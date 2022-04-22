CC=g++ --coverage
CFLAGS=--std=c++11 -Wall -Wextra -ggdb3 -D INFO_ON  -D WARN_ON 
# DEBUG=  -D DEBUG_ON -D VERBEUX_ON  -D DEBUG_ECHEQUE -D DEBUG_EMP
SRC := parties
SOURCES := $(wildcard $(SRC)/*.auchan)
OBJECTS := $(patsubst $(SRC)/%.auchan, $(SRC)/%-valgrind, $(SOURCES))

.PHONY: clean

#tests les leaks
all:	$(OBJECTS)
	cat $^
	grep "LEAK SUMMARY:" -A 6 $^
	for number in {4..6};do ./test-level.sh $$number;done
	touch all

#execute un test unitaire
%: parties/%.auchan echecs
	valgrind --track-origins=yes --leak-check=full  ./echecs < <(cat $< | grep -v '#')

### Génère l'executable
echecs : main.o echiquier.o square.o jeu.o piece.o
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

main.o : main.cc jeu.hh square.hh echiquier.hh  macro.hh
	$(CC) $(CFLAGS) $(DEBUG) -c $<

echiquier.o : echiquier.cc echiquier.hh piece.hh square.hh
	$(CC) $(CFLAGS) $(DEBUG) -c $<

jeu.o : jeu.cc jeu.hh echiquier.hh
	$(CC) $(CFLAGS) $(DEBUG) -c $<

square.o : square.cc square.hh macro.hh
	$(CC) $(CFLAGS) $(DEBUG) -c $<

piece.o : piece.cc piece.hh
	$(CC) $(CFLAGS) $(DEBUG) -c $<


###fonction 
clean:
	rm -rf *.gch *.dSYM *.o echecs *~ vgcore.* parties/*-valgrind all out *.gcda *.gcno coverage.info test.log
	
#force la recompilation (utile quand on change les flag)
r:
	make clean
	make echecs

#génère fichier cache de débug 
$(SRC)/%-valgrind: $(SRC)/%.auchan echecs
	echo -e "\n================ $< =================" > $@
	valgrind --track-origins=yes --leak-check=full ./echecs < <(cat $< | grep -v '#') 2>> $@ 

#print le cache de débug
r%: parties/%-valgrind
	cat $^

#génère un raport lcove
lcov: all
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
	# firefox out/
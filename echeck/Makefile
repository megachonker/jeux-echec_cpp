CC=g++
CFLAGS=--std=c++11 -Wall -Wextra -ggdb3 -D INFO_ON 
# DEBUG= -D WARN_ON -D VERBEUX_ON -D DEBUG_ON -O3



.PHONY: clean

#tests les leaks
all:	parties/themove-valgrind parties/pion-valgrind parties/rock-valgrind parties/pat-valgrind parties/mat-valgrind parties/sebmove-valgrind
	cat $^
	grep "LEAK SUMMARY:" -A 6 $^
	for number in {4..6};do ./test-level.sh $$number;done
	touch all


#execute un test unitaire
%: parties/%.auchan echecs
	valgrind --track-origins=yes --leak-check=full  ./echecs < $^

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
	rm -rf *.gch *.dSYM *.o echecs *~ vgcore.* parties/*-valgrind all

#génère fichier cache de débug 
%-valgrind: %.auchan echecs
	echo -e "\n================ $< =================" > $@
	valgrind --track-origins=yes --leak-check=full ./echecs < $< 2>> $@ 

#print le cache de débug
r%: parties/%-valgrind
	cat $^
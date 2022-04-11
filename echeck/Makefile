CC=g++
CFLAGS=--std=c++11 -Wall -Wextra -ggdb3
DEBUG=  -D INFO_ON -D WARN_ON
# -D VERBEUX_ON -D DEBUG_ON
# -O2
DFLAGS=DEBUG

test:	echecs pion

r%: %-valgrind
	cat $^

%-valgrind: %.auchan echecs
	valgrind --track-origins=yes --leak-check=full ./echecs < $^ 2> $@ 

%: %.auchan
	valgrind --track-origins=yes --leak-check=full  ./echecs < $^


all:	themove-valgrind pion-valgrind rock-valgrind	pat-valgrind mat-valgrind sebmove-valgrind
	grep "LEAK SUMMARY:" -A 6 $^


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

clean:
	rm -rf *.gch *.dSYM *.o echecs *~ vgcore.* *-valgrind



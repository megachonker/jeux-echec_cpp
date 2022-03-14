CC=g++
CFLAGS=--std=c++11 -Wall -Wextra -ggdb
# -O2
DFLAGS=DEBUG

target : echecs themove.auchan
	cat pion.auchan|valgrind --track-origins=yes --leak-check=full ./echecs

echecs : main.o echiquier.o square.o jeu.o piece.o
	$(CC) $(CFLAGS) $^ -o $@

main.o : main.cc jeu.hh square.hh echiquier.hh
	$(CC) $(CFLAGS) -c $<

echiquier.o : echiquier.cc echiquier.hh piece.hh square.hh
	$(CC) $(CFLAGS) -c $<

jeu.o : jeu.cc jeu.hh echiquier.hh
	$(CC) $(CFLAGS) -c $<

square.o : square.cc square.hh
	$(CC) $(CFLAGS) -c $<

piece.o : piece.cc piece.hh
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.gch *.dSYM *.o echecs *~ vgcore.*



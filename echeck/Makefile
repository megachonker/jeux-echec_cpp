CC=g++
CFLAGS=--std=c++11 -Wall -Wextra -ggdb -O2
DFLAGS=DEBUG

target : echecs

echecs : main.cc echiquier.o square.o jeu.o
	$(CC) $(CFLAGS) $< -o $@

echiquier.o : echiquier.cc echiquier.hh piece.o square.o
	$(CC) $(CFLAGS) -c echiquier.cc

jeu.o : jeu.hh jeu.cc
	$(CC) $(CFLAGS) -c jeu.cc

square.o : square.cc square.hh
	$(CC) $(CFLAGS) -c square.cc

piece.o : piece.cc piece.hh
	$(CC) $(CFLAGS) -c piece.cc

clean:
	rm -rf *.dSYM *.o echecs *~



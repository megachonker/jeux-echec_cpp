CC=g++
CFLAGS=--std=c++11 -Wall -Wextra -ggdb
DEBUG= -D VERBEUX_ON -D DEBUG_ON -D INFO_ON -D WARN_ON 
# -O2
DFLAGS=DEBUG

target : echecs themove.auchan
	valgrind --track-origins=yes --leak-check=full ./echecs < themove.auchan
debug : echecs themove.auchan
	gdb ./echecs
	run < themove.auchan

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
	rm -rf *.gch *.dSYM *.o echecs *~ vgcore.*



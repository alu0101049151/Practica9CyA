
CC=g++
CXXFLAGS=-std=c++11 -g

OBJS= GSymbols.o Production.o Grammar.o mainG2CNF.o
all: ${OBJS}
	$(CC) $(CXXFLAGS) -o G2CNF ${OBJS}

clean:
	rm -rf *.o *.txt *.gv *.nfa *.gra G2CNF

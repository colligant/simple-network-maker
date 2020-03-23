CC=g++-9
CFLAGS=-I -O3 -std=c++11

all: graph.out

graph.tab.c: graph.y
	bison -d graph.y

lex.yy.c: graph.l
	flex graph.l

graph.out: graph.l graph.y graph.tab.c lex.yy.c
	$(CC) $(CFLAGS) graph.tab.c lex.yy.c -ll -o graph.out

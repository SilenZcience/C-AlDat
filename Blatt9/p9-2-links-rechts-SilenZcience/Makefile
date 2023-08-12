CC=gcc
CFLAGS=-g -Wall

all: treetest

bintree.o: bintree.h
treetest: bintree.h

treetest: bintree.o treemain.o
	${CC} ${CFLAGS} -o treetest bintree.o treemain.o

clean:
	rm -f treetest
	rm -f *.o

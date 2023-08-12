CC=gcc
CFLAGS=-g -Wall -Werror#-fsanitize=address,undefined

all: pqtest treetest

bintree.o: bintree.h
prioqueue.o: prioqueue.h
main.o: bintree.h prioqueue.h

pqtest: bintree.o prioqueue.o main.o
	${CC} ${CFLAGS} -o pqtest bintree.o prioqueue.o main.o

treetest: bintree.o treemain.o
	${CC} ${CFLAGS} -o treetest bintree.o treemain.o

clean:
	rm -f treetest
	rm -f pqtest
	rm -f *.o

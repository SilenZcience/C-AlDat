CC=gcc
CFLAGS=-Wall -Werror -g
OBJECTS=treemain.o bintree.o dlinkedlist.o

all: levels

treemain.o: bintree.h
bintree.o: bintree.h
dlinkedlist.o: dlinkedlist.h

levels: ${OBJECTS}
	${CC} ${CFLAGS} -o levels ${OBJECTS}

clean:
	rm -f levels
	rm -f ${OBJECTS}

.PHONY: clean all

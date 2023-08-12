CC=gcc
CFLAGS=-g3 -Wall #-fsanitize=address,undefined
# TODO Geben Sie über das Makro an, welche Datenstruktur für den Graphen genutzt werden soll
MAKROS=-DLISTE
# TODO ergänzen Sie die notwendigen Objekte
OBJECTS=adjacencyList.o dlinkedlist.o stack.o


all: topsort

arraylist.o: arraylist.h arraylist.c
dlinkedlist.o: dlinkedlist.h dlinkedlist.c
adjacencyList.o: adjacencyList.h dlinkedlist.h adjacencyList.c dlinkedlist.c
adjacencyMatrix.o: adjacencyMatrix.h adjacencyMatrix.c 
stack.o: stack.c stack.h
queue.o: queue.c queue.h

topsort: ${OBJECTS} topsort.c
	${CC} ${MAKROS} ${CFLAGS} -o topsort topsort.c ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f topsort
 

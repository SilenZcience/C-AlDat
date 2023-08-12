CC=gcc
CFLAGS=-g3 -Wall

OBJECTS=eiswagen.o arraylist.o dlinkedlist.o

all: eiswagen

eiswagen.o: arraylist.h eiswagen.h dlinkedlist.h
arraylist.o: arraylist.h eiswagen.h
dlinkedlist.o: dlinkedlist.h

eiswagen: ${OBJECTS}
	${CC} ${CFLAGS} -o eiswagen ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f arraylist

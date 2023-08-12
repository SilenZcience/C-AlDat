CC=gcc
CFLAGS=-g3 -Wall

OBJECTS=main.o arraylist.o

all: arraylist

main.o: arraylist.h
arraylist.o: arraylist.h

arraylist: ${OBJECTS}
	${CC} ${CFLAGS} -o arraylist ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f arraylist

CC=gcc
CFLAGS=-Wall -Werror -g #-fsanitize=address,undefined

OBJECTS=main.o io.o mergesort.o dlinkedlist.o

all: sortlist listtest

io.o: io.h
mergesort.o: mergesort.h
main.o: io.h mergesort.h

sortlist: ${OBJECTS}
	${CC} ${CFLAGS} -o sortlist ${OBJECTS}

listtest: dlinkedlist.o listtest.o
	${CC} ${CFLAGS} -o listtest dlinkedlist.o listtest.o

clean:
	rm -f sortlist
	rm -f ${OBJECTS}
	rm -f listtest.o
	rm -f listtest


.PHONY: all clean

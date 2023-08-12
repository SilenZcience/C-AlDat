CC=gcc
CFLAGS=-Wall -g
OBJECTS=main.o binheap_array.o binheap.o

all: pm

main.o: project.h binheap.h main.c
binheap_array.o: binheap_array.h binheap_array.c
binheap.o: binheap_array.h binheap.c
binheap.h: project.h

pm: ${OBJECTS}
	${CC} ${CFLAGS} -o pm ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f pm


.PHONY: all clean


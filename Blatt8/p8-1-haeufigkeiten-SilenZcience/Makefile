CC=gcc
CFLAGS=-Wall -g
OBJECTS=hashmap.o main.o arraylist.o mergesort.o

all: wordcount

hashmap.o: hashmap.h ilist.h
main.o: hashmap.h ilist.h arraylist.h mergesort.h
arraylist.o: arraylist.h
mergesort.o: mergesort.h

wordcount: ${OBJECTS} 
	${CC} ${CFLAGS} -o wordcount ${OBJECTS}

clean: 
	rm -f wordcount
	rm -f ${OBJECTS}

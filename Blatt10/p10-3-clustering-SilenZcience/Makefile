CC=gcc
CFLAGS=-Wall -Werror -g
OBJECTS=main.o unionfind.o mergesort.o graph.o

all: cluster

main.o: unionfind.h mergesort.h graph.h
unionfind.o: unionfind.h graph.h
mergesort.o: mergesort.h graph.h

cluster: ${OBJECTS}
	${CC} ${CFLAGS} -o cluster ${OBJECTS}

clean:
	rm -f cluster
	rm -f ${OBJECTS}

.PHONY: clean all

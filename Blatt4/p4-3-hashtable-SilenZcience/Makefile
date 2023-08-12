CC=gcc
CFLAGS=-Wall -Werror -g -fsanitize=undefined
BIN=birds
OBJECTS=main.o hashtable.o

all: ${BIN}

main.o: hashtable.h
hashtable.o: hashtable.c hashtable.h

${BIN}: ${OBJECTS}
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f ${BIN}

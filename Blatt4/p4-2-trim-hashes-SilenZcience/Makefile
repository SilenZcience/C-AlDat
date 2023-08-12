CC=gcc
CFLAGS=-Wall -Werror -g
OBJECTS=trim.o main.o
BIN=trim

.PHONY: all clean

all: trim

trim.o: trim.h trim.c
main.o: trim.h main.c

${BIN}: ${OBJECTS}
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f ${BIN}

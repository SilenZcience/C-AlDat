CC=gcc
CFLAGS=-Wall -Werror -g -fsanitize=undefined
OBJECTS=main.o unionfind.o
BIN=unionfind

all: ${BIN}

main.o: main.c unionfind.h
unionfind.o: unionfind.c unionfind.h

${BIN}: ${OBJECTS}
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f ${BIN}

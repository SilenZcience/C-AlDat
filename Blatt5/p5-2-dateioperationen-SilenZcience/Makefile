CC=gcc
CFLAGS=-Wall -g -fsanitize=undefined
OBJECTS=main.o
BIN=sum

all: ${BIN}

main.o: main.c

${BIN}: ${OBJECTS}
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f ${BIN}

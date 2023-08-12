CC=gcc
CFLAGS=-Wall -Werror -g -fsanitize=undefined
BIN=pointererror
OBJECTS=main.o

all: ${BIN}

main.o: main.c

${BIN}: ${OBJECTS}
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f ${BIN}

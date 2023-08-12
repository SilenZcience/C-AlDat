.PHONY: all clean

CC=gcc
CFLAGS=-Wall -Werror
BIN=fracdemo
OBJECTS=io.o fraction.o genmath.o main.o

all: ${BIN}

fraction.o: genmath.h
io.h: fraction.h
main.o: io.h genmath.h fraction.h

${BIN}: ${OBJECTS}
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f ${BIN}

CC=gcc
CFLAGS=-g3 -Wall

OBJECTS=main.o tokenizer.o

all: tokenizer

main.o: main.c tokenizer.h
tokenizer.o: tokenizer.c tokenizer.h

tokenizer: ${OBJECTS}
	${CC} ${CFLAGS} -o tokenizer ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	rm -f tokenizer

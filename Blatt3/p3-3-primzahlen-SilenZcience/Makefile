CC = gcc

BIN    = primes
CFLAGS = -Wall -g

SRCS := $(shell find *.c)
OBJS := $(addsuffix .o,$(basename $(SRCS)))

all: ${BIN}


main.o: main.c primes.h
primes.o: primes.c primes.h


$(BIN): $(OBJS)
	${CC} ${CFLAGS} -o ${BIN} $(OBJS)


clean:
	rm -f ${BIN} $(OBJS)


.PHONY: all clean

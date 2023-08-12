CC = gcc

BIN    = linalg
CFLAGS = -Wall -Werror -g
DEBUG  = -DCA_DEBUG

SRCS := $(shell find *.c)
OBJS := $(addsuffix .o,$(basename $(SRCS)))

all: $(BIN)


main.o: main.c point.h io.h pointmath.h
io.o: io.c io.h debug.h point.h
	${CC} ${CFLAGS} -c ${DEBUG} -o io.o io.c
pointmath.o: pointmath.c pointmath.h point.h


$(BIN): $(OBJS)
	${CC} ${CFLAGS} -o ${BIN} $(OBJS)


clean:
	rm -f ${BIN} $(OBJS)


.PHONY: all clean

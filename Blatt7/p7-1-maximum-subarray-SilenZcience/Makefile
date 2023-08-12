CC=gcc
CFLAGS=-Wall -Werror -O2

all: msa randnums

msa: max-sub-array.c
	${CC} ${CFLAGS} -o msa max-sub-array.c

randnums: randnums.c
	${CC} ${CFLAGS} -o randnums randnums.c

clean:
	rm -f msa
	rm -f randnums
	rm -f *.o

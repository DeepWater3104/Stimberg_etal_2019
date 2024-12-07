TARGET = run

#CC = gcc
#CFLAGS_K = -Wall -O2

CC = fccpx
#CFLAGS_K = -Ofast -fopenmp -std=c11 -fvectorize -Rpass=.* -ffj-lst=t -DMPI -Nclang -mcpu=a64fx
#CFLAGS_K = -Ofast -fopenmp -std=c11 -fvectorize -ffj-lst=t -DMPI -Nclang -mcpu=a64fx
CFLAGS_K = -Ofast -std=c11 -ffj-lst=t -Nclang -mcpu=a64fx -ffj-fjprof

CFILES = simulate.c TMsynapse.c LIFneuron.c IOput.c

SFMTDIR = ../misc/SFMT
SFMTFLAGS = -I$(SFMTDIR) -DSFMT_MEXP=19937

OBJS = ${CFILES:.c=.o}
LIB = -lm

${TARGET} : ${OBJS} SFMT.o timer.o
	${CC} ${CFLAGS_K} -o $@ $^ ${LIB}

.SUFFIXES: .c .o
.c.o :
	${CC} -c ${CFLAGS_K} $(SFMTFLAGS) $<

timer.o: ../misc/timer.c
	$(CC) $(CFLAGS_K) -c $<

SFMT.o: $(SFMTDIR)/SFMT.c $(SFMTDIR)/SFMT.h
	$(CC) $(CFLAGS_K) $(SFMTFLAGS) -c $<

clean:
	rm -f *.o

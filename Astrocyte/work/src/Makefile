TARGET = run

#CC = mpifccpx
#CC = mpicc
CC = gcc
#CFLAGS_K = -Ofast -std=c11 -ffj-lst=t -DMPI -Nclang -mcpu=a64fx
CFLAGS_K = -Wall -O2
#CFILES = simulate.c network.c xu-clancy.c IOput.c
#CFILES = LIFneuron.c
CFILES = simulate.c modifiedLiRinzel.c synapse.c gaussian.c

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

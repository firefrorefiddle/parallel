LIBS=-lrt
OMPFLAGS=-fopenmp
COMMON_HEADERS=common.h helper.h
LD=gcc

CC=gcc -c -O3 $(OPT)

all: prefixsums

prefixsums: prefixsums.o rec_openmp.o nrec_openmp.o time.o helper.o seq.o $(COMMON_HEADERS)
	$(LD) -o prefixsums prefixsums.o rec_openmp.o nrec_openmp.o seq.o time.o helper.o $(LIBS) $(OMPFLAGS)

prefixsums.o: prefixsums.c $(COMMON_HEADERS)
	$(CC) prefixsums.c

rec_openmp.o: rec_openmp.c rec_openmp.h $(COMMON_HEADERS)
	$(CC) rec_openmp.c $(OMPFLAGS)

nrec_openmp.o: nrec_openmp.c nrec_openmp.h $(COMMON_HEADERS)
	$(CC) nrec_openmp.c $(OMPFLAGS)

seq.o: seq.c seq.h $(COMMON_HEADERS)
	$(CC) seq.c

time.o: time.c time.h $(COMMON_HEADERS)
	$(CC) time.c

helper.o: helper.c $(COMMON_HEADERS)
	$(CC) helper.c

clean:
	rm -f *.o prefixsums

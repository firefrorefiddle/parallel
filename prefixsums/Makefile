LIBS=-lrt
OMPFLAGS=-fopenmp
COMMON_HEADERS=../common/common.h ../common/helper.h ../common/timing.h
COMMON_OBJS=../common/timing.o ../common/helper.o
LD=gcc

CC=gcc -I../common -c -O3 $(OPT)

all: prefixsums

prefixsums: prefixsums.o rec_openmp.o nrec_openmp.o seq.o dbl_openmp.o $(COMMON_HEADERS) $(COMMON_OBJS)
	$(LD) -o prefixsums prefixsums.o rec_openmp.o nrec_openmp.o seq.o dbl_openmp.o $(COMMON_OBJS) $(LIBS) $(OMPFLAGS) 

prefixsums.o: prefixsums.c $(COMMON_HEADERS)
	$(CC) prefixsums.c

rec_openmp.o: rec_openmp.c rec_openmp.h $(COMMON_HEADERS)
	$(CC) rec_openmp.c $(OMPFLAGS)

nrec_openmp.o: nrec_openmp.c nrec_openmp.h $(COMMON_HEADERS)
	$(CC) nrec_openmp.c $(OMPFLAGS)

dbl_openmp.o: dbl_openmp.c dbl_openmp.h $(COMMON_HEADERS)
	$(CC) dbl_openmp.c $(OMPFLAGS)

seq.o: seq.c seq.h $(COMMON_HEADERS)
	$(CC) seq.c

../common/timing.o: $(COMMON_HEADERS)
	cd ../common; make; cd $(OLDPWD)

../common/helper.o: $(COMMON_HEADERS)
	cd ../common; make; cd $(OLDPWD)

clean:
	rm -f *.o prefixsums $(COMMON_OBJS)

LIBS=-lrt
OMPFLAGS=-fopenmp
COMMON_HEADERS=common.h helper.h

all: prefixsums

prefixsums: rec_openmp.o time.o helper.o $(COMMON_HEADERS)
	gcc -o prefixsums prefixsums.c rec_openmp.o time.o helper.o $(LIBS) $(OMPFLAGS)

rec_openmp.o: rec_openmp.c rec_openmp.h $(COMMON_HEADERS)
	gcc -c rec_openmp.c $(OMPFLAGS)

time.o: time.c time.h $(COMMON_HEADERS)
	gcc -c time.c

helper.o: helper.c $(COMMON_HEADERS)
	gcc -c helper.c

clean:
	rm -f *.o prefixsums
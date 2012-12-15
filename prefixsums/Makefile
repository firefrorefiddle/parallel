LIBS=-lrt
FLAGS=-fopenmp

all: rec_openmp

rec_openmp: rec_openmp.c time.o
	gcc -o rec_openmp rec_openmp.c time.o $(LIBS) $(FLAGS)

time.o: time.c time.h
	gcc -c time.c

clean:
	rm -f *.o rec_openmp
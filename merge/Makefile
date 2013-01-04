LIBS=-lrt
OMPFLAGS=-fopenmp
COMMON_HEADERS=../common/common.h ../common/helper.h ../common/timing.h
COMMON_OBJS=../common/timing.o ../common/helper.o
LD=gcc

CC=gcc -I../common -c -O3 $(OPT)

all: merge

merge: merge.o $(COMMON_HEADERS) $(COMMON_OBJS)
	$(LD) -o merge merge.o $(COMMON_OBJS) $(LIBS) $(OMPFLAGS) 

merge.o: merge.c $(COMMON_HEADERS)
	$(CC) merge.c

../common/timing.o: $(COMMON_HEADERS)
	cd ../common; make; cd $(OLDPWD)

../common/helper.o: $(COMMON_HEADERS)
	cd ../common; make; cd $(OLDPWD)

clean:
	rm -f *.o merge $(COMMON_OBJS)

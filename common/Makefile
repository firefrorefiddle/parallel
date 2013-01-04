CC=gcc -c -O3 $(OPT)

all: timing.o helper.o

Timing.o: timing.c timing.h common.h
	$(CC) timing.c

helper.o: helper.c helper.h common.h
	$(CC) helper.c

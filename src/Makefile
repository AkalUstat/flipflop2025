CC=gcc
CFLAGS=-g -Wall

clean:
	rm -rf *.o
	rm -rf day3


day3: day3.o array.o
	$(CC) $(CFLAGS) -o day3.out day3.o array.o

day3.o: day3.c
	$(CC) $(CFLAGS) -c day3.c -o day3.o

array.o: array.c array.h
	$(CC) $(CLFAGS) -c array.c
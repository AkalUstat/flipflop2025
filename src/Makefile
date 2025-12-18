CC=gcc
CFLAGS=-g -Wall

clean:
	rm -rf *.o
	rm -rf day3
	rm -rf 4.day


day3: day3.o array.o
	$(CC) $(CFLAGS) -o day3.out day3.o array.o

day4: day4.o array.o
	$(CC) $(CFLAGS) -o 4.day day4.o array.o

day4.o: day4.c
	$(CC) $(CFLAGS) -c day4.c -o day4.o

day3.o: day3.c
	$(CC) $(CFLAGS) -c day3.c -o day3.o

array.o: array.c array.h
	$(CC) $(CLFAGS) -c array.c
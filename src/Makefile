CC=gcc
CFLAGS=-g -Wall

clean:
	rm -rf *.o
	rm -rf day3
	rm -rf 4.day
	rm -rf 5.day
	rm -rf 6.day
	rm -rf 7.day


day3: day3.o array.o
	$(CC) $(CFLAGS) -o day3.out day3.o array.o

day4: day4.o array.o
	$(CC) $(CFLAGS) -o 4.day day4.o array.o

day7: day7.o array.o
	$(CC) $(CFLAGS) -o 7.day day7.o array.o
day6: day6.o array.o
	$(CC) $(CFLAGS) -o 6.day day6.o array.o
day5: day5.o array.o
	$(CC) $(CFLAGS) -o 5.day day5.o array.o
day7.o: day7.c
	$(CC) $(CFLAGS) -c day7.c -o day7.o
day6.o: day6.c
	$(CC) $(CFLAGS) -c day6.c -o day6.o
day5.o: day5.c
	$(CC) $(CFLAGS) -c day5.c -o day5.o
day4.o: day4.c
	$(CC) $(CFLAGS) -c day4.c -o day4.o

day3.o: day3.c
	$(CC) $(CFLAGS) -c day3.c -o day3.o

array.o: array.c array.h
	$(CC) $(CLFAGS) -c array.c

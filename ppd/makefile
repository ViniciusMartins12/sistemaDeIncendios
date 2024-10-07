CC=gcc
CFLAGS=-pthread

all: main

main: main.o functions.o
	$(CC) -o main main.o functions.o $(CFLAGS)

main.o: main.c functions.h
	$(CC) -c main.c $(CFLAGS)

functions.o: functions.c functions.h
	$(CC) -c functions.c $(CFLAGS)

clean:
	rm -f *.o main

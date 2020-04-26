CC = gcc
CFLAGS = -g -std=gnu11 -Wall -Wextra -pedantic-errors -O -lm

rastros.out: data.o controller.o interface.o list.o main.o
	$(CC) $(CFLAGS) -o rastros.out data.o controller.o interface.o list.o main.o

data.o: data.c data.h
	$(CC) $(CFLAGS) -c data.c 

controller.o: controller.c controller.h
	$(CC) $(CFLAGS) -c controller.c 

interface.o: interface.c interface.h
	$(CC) $(CFLAGS) -c interface.c 

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c 

main.o: main.c
	$(CC) $(CFLAGS) -c main.c 

clean:
	rm -f *.o
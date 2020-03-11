CC = gcc
CFLAGS = -Wall -I

rastros.out: data.o controller.o interface.o main.o
	$(CC) -o rastros.out data.o controller.o interface.o main.o

data.o: data.c data.h
	$(CC) -c data.c

controller.o: controller.c controller.h
	$(CC) -c controller.c

interface.o: interface.c interface.h
	$(CC) -c interface.c

main.o: main.c
	$(CC) -c main.c

clean:
	rm -f *.o
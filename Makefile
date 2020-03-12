CC = gcc
CFLAGS = -g -Wall

rastros.out: data.o controller.o interface.o main.o
	$(CC) -o rastros.out data.o controller.o interface.o main.o $(CFLAGS)

data.o: data.c data.h
	$(CC) -c data.c $(CFLAGS)

controller.o: controller.c controller.h
	$(CC) -c controller.c $(CFLAGS)

interface.o: interface.c interface.h
	$(CC) -c interface.c $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	rm -f *.o
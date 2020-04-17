CC = gcc
CFLAGS = -g -Wall
LIBS = -lm

rastros.out: data.o controller.o interface.o list.o main.o
	$(CC) -o rastros.out data.o controller.o interface.o list.o main.o $(CFLAGS) $(LIBS)

data.o: data.c data.h
	$(CC) -c data.c $(CFLAGS)

controller.o: controller.c controller.h
	$(CC) -c controller.c $(CFLAGS)

interface.o: interface.c interface.h
	$(CC) -c interface.c $(CFLAGS)

list.o: list.c list.h
	$(CC) -c list.c $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	rm -f *.o
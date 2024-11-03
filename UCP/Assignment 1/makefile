CC = gcc
CFLAGS = -std=c89 -Wall -Wextra



all: box

box: main.c  map.o random.o terminal.o color.o linkedlist.o
	$(CC) $(CFLAGS) -o box main.c  map.o random.o terminal.o color.o linkedlist.o



map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

random.o: random.c random.h
	$(CC) $(CFLAGS) -c random.c

terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

color.o: color.c color.h
	$(CC) $(CFLAGS) -c color.c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.c

clean:
	rm -f *.o box



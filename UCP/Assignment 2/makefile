CC = gcc
CFLAGS = -Wall -pedantic -ansi
OBJ = main.o map.o player.o random.o terminal.o color.o


EXEC = game


game: main.c player.o map.o random.o terminal.o color.o
	$(CC) $(CFLAGS) -o game main.c player.o map.o random.o terminal.o color.o

player.o: player.c player.h
	$(CC) $(CFLAGS) -c player.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

random.o: random.c random.h
	$(CC) $(CFLAGS) -c random.c

terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

color.o: color.c color.h
	$(CC) $(CFLAGS) -c color.c
clean:
	rm -f *.o game



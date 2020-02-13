PROGNAME = tetris

CC = cc68x

OBJ = main.o drawlib.o

$(PROGNAME): $(OBJ)
	$(CC) -g $(OBJ) -o $(PROGNAME)

main.o: main.c drawlib.h
	$(CC) -g -c main.c

drawlib.o: drawlib.c drawlib.h
	$(CC) -g -c drawlib.c

clean:
	!rm $(OBJ) $(PROGNAME)

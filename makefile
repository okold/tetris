PROGNAME = tetris

CC = cc68x

OBJ = main.o drawlib.o blocklib.o

$(PROGNAME): $(OBJ)
	$(CC) -g $(OBJ) -o $(PROGNAME)

main.o: main.c drawlib.h blocklib.h
	$(CC) -g -c main.c

drawlib.o: drawlib.c drawlib.h
	$(CC) -g -c drawlib.c

blocklib.o: blocklib.c blocklib.h drawlib.h
	$(CC) -g -c blocklib.c

clean:
	!rm $(OBJ) $(PROGNAME)

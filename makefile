PROGNAME = tetris

CC = cc68x

OBJ = main.o drawlib.o fontlib.o

$(PROGNAME): $(OBJ)
	$(CC) -g $(OBJ) -o $(PROGNAME)

main.o: main.c drawlib.h fontlib.h
	$(CC) -g -c main.c

drawlib.o: drawlib.c drawlib.h fontlib.h
	$(CC) -g -c drawlib.c

fontlib.o: fontlib.c fontlib.h
	$(CC) -g -c fontlib.c

clean:
	!rm $(OBJ) $(PROGNAME)

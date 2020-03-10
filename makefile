PROGNAME = tetris

CC = cc68x

OBJ = main.o drawlib.o fontlib.o blocklib.o

$(PROGNAME): $(OBJ)
	$(CC) -g $(OBJ) -o $(PROGNAME)

main.o: main.c drawlib.h fontlib.h blocklib.h
	$(CC) -g -c main.c

drawlib.o: drawlib.c drawlib.h fontlib.h
	$(CC) -g -c drawlib.c

fontlib.o: fontlib.c fontlib.h
	$(CC) -g -c fontlib.c

blocklib.o: blocklib.c blocklib.h drawlib.h
	$(CC) -g -c blocklib.c

clean:
	!rm $(OBJ) $(PROGNAME)

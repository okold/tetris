PROGNAME = tetris

CC = cc68x

OBJ = main.o drawlib.o fontlib.o blocklib.o audiolib.o input.o buffer.o

$(PROGNAME): $(OBJ)
	$(CC) -g $(OBJ) -o $(PROGNAME)

main.o: main.c drawlib.h fontlib.h blocklib.h audiolib.h buffer.h
	$(CC) -g -c main.c

drawlib.o: drawlib.c drawlib.h fontlib.h
	$(CC) -g -c drawlib.c

fontlib.o: fontlib.c fontlib.h
	$(CC) -g -c fontlib.c

blocklib.o: blocklib.c blocklib.h drawlib.h
	$(CC) -g -c blocklib.c

audiolib.o: audiolib.c audiolib.h
	$(CC) -g -c audiolib.c	

input.o: input.c input.h
	$(CC) -g -c input.c

buffer.o: buffer.s
	gen -D -L2 buffer.s

clean:
	!rm $(OBJ) $(PROGNAME)

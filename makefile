tetris: main.o drawlib.o
	cc68x -g main.o drawlib.o -o tetris

main.o: main.c drawlib.h
	cc68x -g -c main.c

drawlib.o: drawlib.c drawlib.h
	cc68x -g -c drawlib.c

# this works in my terminal but not in gulam because gulam is stupid
clean:
	rm *.O TETRIS

noughts: main.o func.o
	gcc -o noughts main.o func.o

main.o: main.c noughts.h
	gcc -c -o main.o main.c

func.o: func.c noughts.h
	gcc -c -o func.o func.c

clean:
	rm -f noughts *.o


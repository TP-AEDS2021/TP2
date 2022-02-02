all: 
	gcc -g main.c -o main

clean:
	del *.o *.exe *.h

run: all
	./main

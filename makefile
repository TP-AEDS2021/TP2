all: permuta
	gcc -g main.c -o main

permuta:
	gcc -g ./src/permuta.c -o permuta

clean:
	del *.o *.exe *.h main

run: clean all 
	./main

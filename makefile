all: permuta
	gcc -g main.c -o main

permuta:
	gcc -g ./src/permuta.c -o permuta

clean:
	rm *.o *.exe *.h main *.out

run: all 
	./main

doc:
	md-to-pdf docs.md --document-title="Documentacao TP 1"

teste: 
	gcc teste.c -o teste
run_teste: teste
	./teste
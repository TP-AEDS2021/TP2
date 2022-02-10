all:
	gcc -g main.c -o main

clean:
	rm *.o *.exe *.h main *.out

run: all 
	./main

doc:
	md-to-pdf readme.md --document-title="Documentacao TP 1"

teste: 
	gcc teste.c -o teste
run_teste: teste
	./teste
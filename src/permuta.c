#include <stdio.h>
#include <stdlib.h>
#include "./utils/utils.c"

/* Funcao que retorna verdadeiro se
 * `num' nao contem algarismos repetidos
 * e zero caso contrario. */
char eh_sem_repeticao(int *num, int r) {
    int i, j ;
 
    for(i=0; i < r; i++) {
        for(j=0; j < r && i != j; j++) {
            if(num[i] == num[j]) {
                return 0;
            }
        }
    }
 
    return 1 ;
}
 
int main(int argc, char **argv) {
    /* Vetor de elementos. Coloque quantos elementos
    * quiser, mas o ultimo deve ser sempre NULL. */
    //char *vetor[] = {"pera",  "uva", "maca", "goaiaba", NULL} ; //transformar em entrada por arquivo com NULL no final
    int **matrizDistancias;
    int *demandas;
    int capacidadeCaminhao, nmroCidades, nmroCaminhoes, demandaRota, temVisitada, demandaTotal = 0;
    for(int i = 1; i < nmroCidades; i++)
    {
        demandaTotal += demandas[i];
    }
    nmroCaminhoes = demandaTotal / capacidadeCaminhao;
    int *foiVisitada = (int*) malloc(sizeof(int) * nmroCidades - 1);
    for(int i = 0; i < nmroCidades - 1; i++)
    {
        foiVisitada[i] = False;
    }
    int *vetor = (int*) malloc(sizeof(int) * nmroCidades);
    for(int i = 1; i <= nmroCidades; i++)
    {
        if(i != nmroCidades) vetor[i - 1] = i;
        else vetor[i] = -1;
    }
    //int vetor[4] = {1, 2, 3, -1}; //teste

    /* vetor que representara cada permutacao. */
    int *num ;
    /* quantidade de elementos do vetor. */
    int n ;
    /* tamanho de cada permutacao. */
    int r ;
    /* controle de loop. */
    int i, j ;
 
    /* Obtem a quantidade de elementos do vetor. */
    n=0;
    while ( vetor[n] != -1 ) n++ ;
 
    /* Testa parametros da linha de comando. */
    //if ( argc > 1 ) {
    //    r = atoi(argv[1]) ;
    //} else {
    //    r = n ;
    //}
 
    /* Sai do programa se r > n. */
    //if ( r > n ) {
    //    printf("Nao faz sentido r > n.\n") ;
    //    return -1 ;
    //}
 
    /* Aloca espaco para o vetor num. Lembre-se
     * que o vetor `num' representa um numero
     * na base n com r algarismos. */
    for(r = 1; r <= n; r++)
    {
        num = (int *)calloc(r+1, sizeof(int)) ;
        if ( num == NULL ) {
            perror("malloc") ;
            return -1;
        }
        /* Inicio do algoritmo. */
        while ( num[r] == 0 ) {
            for(i=0; i < n; i++) {
                /* Mostra a permutacao na tela se
                * e somente se `num' nao contem
                * algarismos repetidos. */
                if ( eh_sem_repeticao(num, r) ) {
                    //calcula a demanda da rota
                    demandaRota = 0;
                    for(j=0; j < r; j++) {
                        demandaRota += demandas[vetor[num[j]]];
                        //printf("%d ", vetor[num[j]]) ;
                    }
                    //verifica se a demanda das cidades da rota eh maior do que a capacidade do caminhao
                    if(demandaRota <= capacidadeCaminhao)
                    {
                        //somar distancias
                    }
                    //putchar('\n') ;
                }
    
                /* incrementa o algarismo menos
                * significativo. */
                num[0]++ ;
            }
    
            /* distribui os vai-uns. */
            for(i=0; i < r; i++) {
                if(num[i] == n) {
                    num[i] = 0;
                    num[i+1]++ ;
                }
            }
        }
    
        free(num) ;
    }
 
    return 0;
}
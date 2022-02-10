#include <stdio.h>
#include <stdlib.h>
 
/* Vetor de elementos. Coloque quantos elementos
 * quiser, mas o ultimo deve ser sempre NULL. */
//char *vetor[] = {"1",  "2", "3", "4", NULL} ; //transformar em entrada por arquivo com NULL no final

 
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

int * selecPerm(int *cidades, int *visitadas, int n)
{
    // V = cidades nao visitadas
    // contador para quantas cidades nao foram visitadas
    int count = 0;
    // conta o numero de cidades que nao foram visitadas
    for(int i = 0; i < n; i++)
    {
        if(visitadas[i] == 0) count++;
    }
    // cria e preenche o vetor que sera permutado, apenas com as cidades que nao foram visitadas
    int *perm = (int*) malloc(sizeof(int) * count); // cria o vetor de tamanho V
    int k = 0; // variavel para continuar a contagem do vetor com todas as cidades de onde parou
    for(int i = 0; i < count; i++) // preenche o vetor de tamanho V com as cidades que nao foram visitadas
    {
        for(int j = k; j < n; j++)
        {
            if(visitadas[j] == 0)
            {
                perm[i] = cidades[j];
                k = j + 1;
                break;
            }
            k = j + 1;
        }
    }
    return perm;
}

int calcNaoVisitadas(int *cidades, int *visitadas, int n)
{
    // V = cidades nao visitadas
    // contador para quantas cidades nao foram visitadas
    int count = 0;
    // conta o numero de cidades que nao foram visitadas
    for(int i = 0; i < n; i++)
    {
        if(visitadas[i] == 0) count++;
    }
    return count;
}
 
int main(int argc, char **argv) {
    #pragma region variaveis
    // N = numero de cidades
    // capacidade dos caminhoes, numero de cidades, numero de caminhoes, numero de cidades nao visitadas, controle para verificar se a rota eh valida demanda da rota atual, distancia da rota atual, distancia da menor rota geral, demanda total
    int capacidadeCaminhoes, nmroCidades, nmroCaminhoes, nmroCidadesNaoVisitadas, temEstrada, demandaRota, distanciaRota, distanciaMenorRota, demandaTotal = 0;
    // printf("Numero de cidades: ");
    // scanf("%d", &nmroCidades);
    // printf("Capacidade caminhoes: ");
    scanf("%d", &capacidadeCaminhoes);
    // printf("Demandas:\n");
    // cria e preenche o vetor das demandas com entradas do teclado, de tamanho N
    int *vetorDemandas = (int*) malloc(sizeof(int) * nmroCidades);
    // for(int i = 0; i < nmroCidades; i++) // preenchimento do vetor por entradas no teclado
    // {
    //     scanf("%d", &vetorDemandas[i]);
    // }
    // calcula a demanda total
    for(int i = 0; i < nmroCidades; i++)
    {
        demandaTotal += vetorDemandas[i];
    }
    // calcula o numero de caminhoes
    nmroCaminhoes = demandaTotal / capacidadeCaminhoes;
    // cria e preenche o vetor das cidades com numeros de 0 a N-1, de tamanho N
    int *vetorCidades = (int*) malloc(sizeof(int) * nmroCidades);
    for(int i = 0; i < nmroCidades; i++) // preenche o vetor com 0 a N-1
    {
        vetorCidades[i] = i;
    }
    // cria e preenche o vetor que verifica se a cidade foi visitada com 0s, exceto pela posicao 0(deposito), de tamanho N
    int *vetorVisitadas = (int*) malloc(sizeof(int) * nmroCidades);
    vetorVisitadas[0] = 1; // preenche a posicao 0 do vetor(deposito) com 1
    for(int i = 1; i < nmroCidades; i++) // preenche as outras posicoes do vetor com 0
    {
        vetorVisitadas[i] = 0;
    }
    // cria e preenche a matriz das distancias com entradas do teclado, de tamanho NxN
    int **matrizDistancias = (int**) malloc(sizeof(int*) * nmroCidades);
    // printf("Distancias:\n");
    // for(int i = 0; i < nmroCidades; i++) // preenche a matriz por entradas do teclado
    // {
    //     matrizDistancias[i] = (int*) malloc(sizeof(int) * nmroCidades);
    //     for(int j = 0; j < nmroCidades; j++)
    //     {
    //         scanf("%d", &matrizDistancias[i][j]);
    //     }
    // }
    // 
    nmroCidadesNaoVisitadas = calcNaoVisitadas(vetorCidades, vetorVisitadas, nmroCidades);
    // cria e preenche o vetor que sera permutado, apenas com as cidades que nao foram visitadas
    int *vetorPerm = selecPerm(vetorCidades, vetorVisitadas, nmroCidades);
    // vetor da rota atual
    int *vetorRota;
    // vetor da menor rota geral
    int *vetorMenorRota;
    int **matrizRotas = (int**) malloc(sizeof(int*) * nmroCaminhoes);
    for(int i = 0; i < nmroCaminhoes; i++)
    {
        matrizRotas[i] = (int*) malloc(sizeof(int) * (nmroCidades + 1));
        for(int j = 0; j < nmroCidades; j++)
        {
            matrizRotas[i][j] = -1;
        }
    }
    putchar('\n');
    int count = 0;

#pragma endregion
   
    do
    {
        /* vetor que representara cada permutacao. */
        int *num ;
        /* quantidade de elementos do vetor. */
        int n ;
        /* tamanho de cada permutacao. */
        int r ;
        /* controle de loop. */
        //int i, j ;
    
        /* Obtem a quantidade de elementos do vetor. */
        n = nmroCidadesNaoVisitadas;
    
        
    
        /* Aloca espaco para o vetor num. Lembre-se
        * que o vetor `num' representa um numero
        * na base n com r algarismos. */
        
        distanciaMenorRota = -1;
        vetorMenorRota = (int*) malloc(sizeof(int) * (nmroCidades + 1));
        for(int i = 0; i <= nmroCidades; i++)
        {
            vetorMenorRota[i] = -1;
        }
        for(r = 1; r <= n; r++)
        {
            num = (int *)calloc(r+1, sizeof(int)) ;
            if ( num == NULL ) {
                perror("malloc") ;
                return -1;
            }
            /* Inicio do algoritmo. */
            while ( num[r] == 0 ) {
                for(int i = 0; i < n; i++) {
                    demandaRota = 0;
                    distanciaRota = 0;
                    vetorRota = (int*) malloc(sizeof(int) * (r + 2));
                    vetorRota[0] = 0;
                    vetorRota[r + 1] = 0;
                    temEstrada = 1;
                    /* Mostra a permutacao na tela se
                    * e somente se `num' nao contem
                    * algarismos repetidos. */
                    if ( eh_sem_repeticao(num, r) ) {
                        for(int j = 0; j < r; j++) {
                            vetorRota[j + 1] = vetorPerm[num[j]];
                            for(int k = 0; k < r; k++)
                            {
                                demandaRota += vetorDemandas[vetorPerm[num[j]]];
                            }
                        }
                        demandaRota /= r;
                        if(demandaRota == capacidadeCaminhoes)
                        {
                            for(int j = 0; j < r + 1; j++)
                            {
                                if(matrizDistancias[vetorRota[j]][vetorRota[j + 1]] == -1)
                                {
                                    temEstrada = 0;
                                    break;
                                }
                            }
                            if(temEstrada == 1)
                            {
                                for(int j = 0; j < r + 1; j++)
                                {
                                    //if(matrizDistancias[vetorRota[j]][vetorRota[j + 1] != -1])
                                    //{
                                        distanciaRota += matrizDistancias[vetorRota[j]][vetorRota[j + 1]];
                                    //}
                                    //else if(matrizDistancias[vetorRota[j]][vetorRota[j + 1] == -1])
                                    //{

                                    //}
                                }
                                if(distanciaMenorRota == -1)
                                {
                                    distanciaMenorRota = distanciaRota;
                                    for(int j = 0; j < r + 2; j++)
                                    {
                                        vetorMenorRota[j] = vetorRota[j];
                                    }
                                }
                                else if(distanciaRota < distanciaMenorRota)
                                {
                                    distanciaMenorRota = distanciaRota;
                                }
                            }
                        }
                    }

                    /* incrementa o algarismo menos
                    * significativo. */
                    num[0]++ ;
                }
        
                /* distribui os vai-uns. */
                for(int i = 0; i < r; i++) {
                    if(num[i] == n) {
                        num[i] = 0;
                        num[i+1]++ ;
                    }
                }
            }
        
            free(num) ;
        }
        printf("vetor menor rota: ");
        for(int i = 0; i <= nmroCidades; i++)
        {
            if(vetorMenorRota[i] != -1) printf("%d ", vetorMenorRota[i]);
        }
        for(int i = 1; i < nmroCidades; i++)
        {
            if(vetorVisitadas[i] == 0)
            {
                for(int j = 1; j < r + 1;j++)
                {
                    if(vetorCidades[i] == vetorMenorRota[j]) vetorVisitadas[i] = 1;
                }
            }
        }
        nmroCidadesNaoVisitadas = calcNaoVisitadas(vetorCidades, vetorVisitadas, nmroCidades);
        vetorPerm = selecPerm(vetorCidades, vetorVisitadas, nmroCidades);
        for (int i = 0; i < nmroCidades + 1; i++)
        {
            matrizRotas[count][i] = vetorMenorRota[i];
        }
        count++;

    }while(nmroCidadesNaoVisitadas != 0);
 
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int nextPerm(int perm[], int k, int n)
{
    bool invalid = true;
    int subject,i;
    if (k == 1)
    {
        if (perm[0] == n - 1)
            return 0;
        else { perm[0]=perm[0]+1; return 1; }
    }
    subject = perm[k - 1]+1;
    while (invalid)
    {
        if (subject == n)
        {
            subject = 0;
            if (!nextPerm(perm, k - 1, n))
                return 0;
        }
        for (i = 0; i < k-1; i++)
        {
            if (perm[i] != subject)
                invalid = false;
            else
            {
                invalid = true;subject++; break; 
            }
        }
    }
    perm[k - 1] = subject;
    return 1;
}
int main()
{
    int demandacam = 15; // demanda do caminhao
    int qtd = 0; //quantidade de rotas possiveis
    int n = 5; //numero de cidades
    int vetorpossivel[] = {-1,-1,-1,-1,-1}; //vetor de possiveis rotas
    int vetorcidades[] = {0,1,2,3,4}; //vetor de cidades
    int permres[] = {0,1,2,3,4}; //vetor cidades reserva
    int demanda[] = {4,8,1,8,2};  //vetor das demandas
    unsigned long long count = 0; //quantidade de arranjos
    int i,j,a; //iteradores
    int **matriz; //matriz de rotas possiveis
    int coluna = n, linha = 0; //limites da matriz
    for(int t =0; t<=1; t++){ //quantidade de rotas(1) + inserção(2)
        if(t==1){
            linha = qtd; //linha = rotas possiveis
            matriz = malloc (linha * sizeof (int*));} //linhas da matriz alocadas dinamicamente
        for (int p=1;p<=n;p++){ //arrajos de tamanho p a n
            int k = p;
            for(int p=0; p<=n-1; p++) vetorcidades[p] =  permres[p]; //atribuição de vetores
                do //inicio do algoritmo
                {   
                    int tot = 0; //soma dos totais das demandas
                    for (a = 0; a < k-1; a++){
                        printf("%d->", vetorcidades[a]+1);
                        tot+= demanda[vetorcidades[a]+1];} //soma as demandas de cada arranjo
                        printf("%d", vetorcidades[k-1]+1);
                        tot += demanda[vetorcidades[k-1]+1];
                        if (tot == demandacam && t==0) qtd+=1; //quantidade de rotas possiveis
                        else if(tot == demandacam  && t==1){
                            for (a = 0; a < k-1; a++) vetorpossivel[a] = vetorcidades[a]+1; //insere a rota em um vetor de apoio
                            vetorpossivel[a]= vetorcidades[k-1]+1;
	                        matriz[i] = malloc (coluna * sizeof (int)); //aloca colunas dinamicamente
	                        for (j=0;j<coluna;j++){
	                            matriz[i][j]= vetorpossivel[j];} //insere na matriz as rotas possiveis
                            i++; //iterador
                        }   
                        count++; //quantidade de arranjos
                        printf(" |Demanda =  %d\n",tot); //imprime a demanda de cada rota
                }
                while (nextPerm(vetorcidades,k,n)); 
                }
    }
    printf("\nNumero de arranjos: %llu\n", count); //qtd de arranjos feitos
    puts("Unicas rotas possiveis:");

    for (int k=0; k < linha; k++){ //imprime a matriz de rotas possiveis
        printf("\n0 ");
        for (int f=0;f<coluna;f++){
            /if (matriz[k][f] != -1)/ printf("%d ", matriz[k][f]);	        
        }
        printf("0");
    };
   return 0;
}
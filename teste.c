#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#ifdef __APPLE__
#include <curses.h>
#elif __WIN32
#include <conio.h>
#define input getch
#elif __linux
#define input getchar
#endif

#define fileStringLength 100

#include <errno.h>

#include "./src/utils/utils.c"

/* Função que verifica se o número é repetido. */
char eh_sem_repeticao(int *num, int r)
{
    int i, j;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r && i != j; j++)
        {
            if (num[i] == num[j])
            {
                return 0;
            }
        }
    }

    return 1;
}

/* Função que seleciona as cidades que serão visitadas. */
int *selecPerm(int *cidades, int *visitadas, int n)
{ // V = cidades nao visitadas
    // contador para quantas cidades nao foram visitadas
    int count = 0;
    // conta o numero de cidades que nao foram visitadas
    for (int i = 0; i < n; i++)
    {
        if (visitadas[i] == 0)
            count++;
    }
    // cria e preenche o vetor que sera permutado, apenas com as cidades que nao foram visitadas
    int *perm = (int *)malloc(sizeof(int) * count); // cria o vetor de tamanho V
    int k = 0;                                      // variavel para continuar a contagem do vetor com todas as cidades de onde parou
    for (int i = 0; i < count; i++)                 // preenche o vetor de tamanho V com as cidades que nao foram visitadas
    {
        for (int j = k; j < n; j++)
        {
            if (visitadas[j] == 0)
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

/* Função que calcula o numero de cidades que não foram visitadas. */
int calcNaoVisitadas(int *visitadas, int numeroDeCidades)
{
    // V = cidades nao visitadas
    // contador para quantas cidades nao foram visitadas
    int count = 0;
    // conta o numero de cidades que nao foram visitadas
    for (int i = 0; i < numeroDeCidades; i++)
    {
        if (visitadas[i] == 0)
            count++;
    }
    return count;
}

int main()
{
    FILE *file, *outputfile;
    char filename[fileStringLength];
    int **distance;
    int **matrizDistancias;
    int *vetorDemandas;
    int temRota = 0;

    int nmroCaminhoes, capacidadeCaminhoes, nmroCidades, nmroCidadesNaoVisitadas, temEstrada, demandaRota, distanciaRota, distanciaMenorRota, demandaTotal = 0;

    do
    {
        cls();
        menu();

        char option = input();

        switch (option)
        {
        case '0':
            exit(0);
            break;

        case '1':
            GREEN()
            puts("Digite o nome do arquivo de testes:");
            YELLOW();
            printf(">> ");
            RESETC();
            scanf("%s", &filename);
            if (filename == NULL || strlen(filename) == 0 || filename[0] == '\0')
            {
                RED()
                puts("Nome do arquivo invalido!");
                RESETC();
                input();
                break;
            }
            file = fopen(filename, "r");
            if (file == NULL)
            {
                RED()
                printf("Erro ao abrir o arquivo %s\n", filename);
                RESETC();
                input();
                break;
            }
            input();
            GREEN();
            printf("Arquivo lido com sucesso\t (pressione enter para continuar)\n");
            input();
            RESETC();
            int nline = 0;
            char buffer[fileStringLength];
            while (fgets(buffer, fileStringLength, file) && !ferror(file))
            {
                if (nline == 0)
                { // Numero de cidades
                    nmroCidades = atoi(buffer);
                    matrizDistancias = (int **)malloc(sizeof(int *) * nmroCidades);
                    if (matrizDistancias == NULL)
                    {
                        perror("malloc");
                        return -1;
                    }

                    for (int i = 0; i < nmroCidades; i++)
                    {
                        matrizDistancias[i] = (int *)malloc(sizeof(int) * nmroCidades);
                    }
                    for (int i = 0; i < nmroCidades; i++)
                    {
                        for (int j = 0; j < nmroCidades; j++)
                        {
                            matrizDistancias[i][j] = -1;
                            if (i == j)
                                matrizDistancias[i][j] = 0;
                        }
                    }

                    YELLOW();
                    printf("Numero de cidades: %d\n", nmroCidades);
                    RESETC();
                }
                else if (nline == 1)
                { // Capacidade do veiculo
                    capacidadeCaminhoes = atoi(buffer);
                    if (capacidadeCaminhoes <= 0)
                    {
                        RED()
                        printf("Capacidade do veiculo invalida\n");
                        RESETC();
                        input();
                        break;
                    }
                    YELLOW();
                    printf("Capacidade do veiculo: %d\n", capacidadeCaminhoes);
                    RESETC();
                }
                else if (nline == 2)
                {
                    // demanda de cada cidade
                    int i = 0;
                    vetorDemandas = (int *)malloc(sizeof(int) * nmroCidades);
                    char *token = strtok(buffer, " ");
                    while (token != NULL)
                    {
                        vetorDemandas[i] = atoi(token);
                        token = strtok(NULL, " ");
                        i++;
                    }

                    YELLOW();
                    printf("Demanda de cada cidade: ");
                    for (int i = 0; i < nmroCidades; i++)
                    {
                        printf("%d ", vetorDemandas[i]);
                    }

                    RESETC();
                }
                else
                {
                    // distancia entre cada cidade
                    int i, j, d;
                    sscanf(buffer, "%d %d %d", &i, &j, &d);

                    matrizDistancias[i][j] = d;
                    matrizDistancias[j][i] = d;
                }
                nline++;
            }
            YELLOW();
            puts("\nDistancia entre cada cidade:");
            PURPLE();
            printf("\n");
            for (int i = 0; i < nmroCidades; i++)
            {
                for (int j = 0; j < nmroCidades; j++)
                {
                    printf("%d ", matrizDistancias[i][j]);
                }
                printf("\n");
            }
            RESETC();
            fclose(file);

            // algoritmo de permutação

#pragma region PERMUTACAO

            for (int i = 0; i < nmroCidades; i++)
            {
                demandaTotal += vetorDemandas[i];
            }
            nmroCaminhoes = demandaTotal / capacidadeCaminhoes;
            printf("\nNumero de caminhoes: %d\n", nmroCaminhoes);
            int *vetorCidades = (int *)malloc(sizeof(int) * nmroCidades);
            for (int i = 0; i < nmroCidades; i++) // preenche o vetor com 0 a N-1
            {
                vetorCidades[i] = i;
            }
            int *vetorVisitadas = (int *)malloc(sizeof(int) * nmroCidades);
            vetorVisitadas[0] = 1;                // preenche a posicao 0 do vetor(deposito) com 1
            for (int i = 1; i < nmroCidades; i++) // preenche as outras posicoes do vetor com 0
            {
                vetorVisitadas[i] = 0;
            }
            nmroCidadesNaoVisitadas = calcNaoVisitadas(vetorVisitadas, nmroCidades);
            int *vetorPerm = selecPerm(vetorCidades, vetorVisitadas, nmroCidades);
            // vetor da rota atual
            int *vetorRota;
            // vetor da menor rota geral
            int *vetorMenorRota;

            // matrix com as rotas a serem criadas
            int **matrizRotas = (int **)malloc(sizeof(int *) * nmroCaminhoes);

            for (int i = 0; i < nmroCaminhoes; i++)
            {
                matrizRotas[i] = (int *)malloc(sizeof(int) * (nmroCidades + 1));
                for (int j = 0; j <= nmroCidades; j++)
                {
                    matrizRotas[i][j] = -1;
                }
            }

            int count = 0;

            time_t tempo_inicial, tempo_final;
            tempo_inicial = 0;
            tempo_final = 0;
            // Seta o tempo inicial para 25/05/2011 14:20:35
            struct tm *tempo_inicial_info = localtime(&tempo_inicial);
            tempo_inicial = mktime(tempo_inicial_info);

            do
            {
                /* vetor que representara cada permutacao. */

                int *num;
                /* quantidade de elementos do vetor. */
                int n;
                /* tamanho de cada permutacao. */
                int r;
                /* controle de loop. */
                // int i, j ;

                /* Obtem a quantidade de elementos do vetor. */
                n = nmroCidadesNaoVisitadas;

                /* Aloca espaco para o vetor num. Lembre-se
                 * que o vetor `num' representa um numero
                 * na base n com r algarismos. */

                distanciaMenorRota = -1;
                free(vetorMenorRota);
                vetorMenorRota = (int *)malloc(sizeof(int) * (nmroCidades + 1));
                for (int i = 0; i <= nmroCidades; i++)
                {
                    vetorMenorRota[i] = -1;
                }

                for (r = 1; r <= n; r++)
                {
                    num = (int *)calloc(r + 1, sizeof(int));
                    if (num == NULL)
                    {
                        perror("malloc");
                        return -1;
                    }
                    /* Inicio do algoritmo. */
                    while (num[r] == 0)
                    {
                        for (int i = 0; i < n; i++)
                        {
                            demandaRota = 0;
                            distanciaRota = 0;
                            free(vetorRota);
                            vetorRota = (int *)malloc(sizeof(int) * (r + 2));
                            vetorRota[0] = 0;
                            vetorRota[r + 1] = 0;
                            temEstrada = 1;
                            /* Mostra a permutacao na tela se
                             * e somente se `num' nao contem
                             * algarismos repetidos. */
                            if (eh_sem_repeticao(num, r))
                            {
                                for (int j = 0; j < r; j++)
                                {
                                    vetorRota[j + 1] = vetorPerm[num[j]];
                                    for (int k = 0; k < r; k++)
                                    {
                                        demandaRota += vetorDemandas[vetorPerm[num[j]]];
                                    }
                                }
                                demandaRota /= r;

                                if (demandaRota == capacidadeCaminhoes)
                                {
                                    for (int j = 0; j < r + 1; j++)
                                    {
                                        if (matrizDistancias[vetorRota[j]][vetorRota[j + 1]] == -1)
                                        {
                                            temEstrada = 0;
                                            break;
                                        }
                                    }
                                    if (temEstrada == 1)
                                    {
                                        for (int j = 0; j < r + 1; j++)
                                        {
                                            distanciaRota += matrizDistancias[vetorRota[j]][vetorRota[j + 1]];
                                        }
                                        if (distanciaMenorRota == -1)
                                        {

                                            distanciaMenorRota = distanciaRota;
                                            for (int j = 0; j < r + 2; j++)
                                            {
                                                vetorMenorRota[j] = vetorRota[j];
                                            }
                                        }

                                        else if (distanciaRota < distanciaMenorRota)
                                        {
                                            distanciaMenorRota = distanciaRota;
                                            for (int j = 0; j < r + 2; j++)
                                            {
                                                vetorMenorRota[j] = vetorRota[j];
                                            }
                                        }
                                    }
                                }
                            }

                            /* incrementa o algarismo menos
                             * significativo. */
                            num[0]++;
                        }

                        /* distribui os vai-uns. */
                        for (int i = 0; i < r; i++)
                        {
                            if (num[i] == n)
                            {
                                num[i] = 0;
                                num[i + 1]++;
                            }
                        }
                    }

                    free(num);
                }
                if (vetorMenorRota[0] != -1)
                {

                    for (int i = 1; i < nmroCidades; i++)
                    {
                        if (vetorVisitadas[i] == 0)
                        {
                            for (int j = 1; j < r + 1; j++)
                            {
                                if (vetorCidades[i] == vetorMenorRota[j])
                                    vetorVisitadas[i] = 1;
                            }
                        }
                    }

                    nmroCidadesNaoVisitadas = calcNaoVisitadas(vetorVisitadas, nmroCidades);
                    vetorPerm = selecPerm(vetorCidades, vetorVisitadas, nmroCidades);
                    for (int i = 0; i < nmroCidades + 1; i++)
                    {
                        matrizRotas[count][i] = vetorMenorRota[i];
                    }

                    count++;
                }
                else
                {
                    RED();
                    printf("\nNao existem mais rotas possiveis\n");
                    RESETC();
                    temRota = -1;
                    break;
                }

            } while (nmroCidadesNaoVisitadas != 0);

            // mostra a matriz de rotas
            YELLOW();

            if (temRota != -1)
            {
                printf("\nVetor de rotas:\n");
                for (int i = 0; i < nmroCaminhoes; i++)
                {
                    for (int j = 0; j < nmroCidades + 1; j++)
                    {
                        if (matrizRotas[i][j] != -1)
                        {
                            if (i == 0)
                            {
                                printf("%d ", matrizRotas[i][j]);
                            }
                            else
                            {
                                if (j != 0)
                                {
                                    printf("%d ", matrizRotas[i][j]);
                                }
                            }
                        }
                    }
                }
            }

#pragma endregion
            struct tm *tempo_final_info = localtime(&tempo_final);
            tempo_final = mktime(tempo_final_info);

            // Calcula a diferença de tempo (segundos)
            double dif = difftime(tempo_final, tempo_inicial);
            printf("\nTempo de execucao: %.8lf segundos\n", dif);
            outputfile = fopen("output.txt", "a");
            fclose(outputfile);
            input();
            break;

        default:
            break;
        }
    } while (1);

    return 0;
}
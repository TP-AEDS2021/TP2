#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

int nextPerm(int perm[], int k, int n)
{
  bool invalid = true;
  int subject, i;
  if (k == 1)
  {
    if (perm[0] == n - 1)
      return 0;
    else
    {
      perm[0] = perm[0] + 1;
      return 1;
    }
  }
  subject = perm[k - 1] + 1;
  while (invalid)
  {
    if (subject == n)
    {
      subject = 0;
      if (!nextPerm(perm, k - 1, n))
        return 0;
    }
    for (i = 0; i < k - 1; i++)
    {
      if (perm[i] != subject)
        invalid = false;
      else
      {
        invalid = true;
        subject++;
        break;
      }
    }
  }
  perm[k - 1] = subject;
  return 1;
}





int main()
{
  FILE *file, *outputfile;
  char filename[fileStringLength];
  int citiesVectorLenght;
  int veichleCapacity;
  int **distance;
  int **arr;
  int *demanda;
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
          citiesVectorLenght = atoi(buffer);
          arr = (int **)malloc(sizeof(int *) * citiesVectorLenght);
          for (int i = 0; i < citiesVectorLenght; i++)
          {
            arr[i] = (int *)malloc(sizeof(int) * citiesVectorLenght);
          }
          for (int i = 0; i < citiesVectorLenght; i++)
          {
            for (int j = 0; j < citiesVectorLenght; j++)
            {
              arr[i][j] = 0;
            }
          }
          YELLOW();
          printf("Numero de cidades: %d\n", citiesVectorLenght);
          RESETC();
        }
        else if (nline == 1)
        { // Capacidade do veiculo
          veichleCapacity = atoi(buffer);
          if (veichleCapacity <= 0)
          {
            RED()
            printf("Capacidade do veiculo invalida\n");
            RESETC();
            input();
            break;
          }
          YELLOW();
          printf("Capacidade do veiculo: %d\n", veichleCapacity);
          RESETC();
        }
        else if (nline == 2)
        {
          // demanda de cada cidade
          int i = 0;
          demanda = (int *)malloc(sizeof(int) * citiesVectorLenght);
          char *token = strtok(buffer, " ");
          while (token != NULL)
          {
            demanda[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
          }

          YELLOW();
          printf("Demanda de cada cidade: ");
          for (int i = 0; i < citiesVectorLenght; i++)
          {
            printf("%d ", demanda[i]);
          }

          RESETC();
        }
        else
        {
          // distancia entre cada cidade
          int i, j, d;
          sscanf(buffer, "%d %d %d", &i, &j, &d);

          arr[i][j] = d;
          arr[j][i] = d;
        }
        nline++;
      }
      YELLOW();
      puts("\nDistancia entre cada cidade:");
      PURPLE();
      printf("\n");
      for (int i = 0; i < citiesVectorLenght -1; i++)
      {
        for (int j = 0; j < citiesVectorLenght - 1 ; j++)
        {
          printf("%d ", arr[i][j]);
        }
        printf("\n");
      }
      RESETC();
      fclose(file);
      // algoritmo de permutação

      #pragma region PERMUTACAO


#pragma endregion

      int capacity = veichleCapacity;
      int qtd = 0;
      int n = citiesVectorLenght - 1;
      int *vetorpossivel = (int *) malloc((n -1) *sizeof(int));
      for (int i = 0; i < n-1; n++)
        vetorpossivel[i] = -1;

      int *vetorcidades = (int *)malloc((n - 1) * sizeof(int));
      for (int i = 0; i < n - 1;i++)
        vetorcidades[i] = i;

      int *permres = (int *)malloc((n - 1) * sizeof(int));
      for (int i = 0; i < n - 1; i++)
        permres[i] = i;
      unsigned long long count = 0;
      int i, j, a;
      int **matriz;
      int coluna = n, linha = 0;
      for (int t = 0; t <= 1; t++)
      { // quantidade de rotas(1) + inserção(2)
        if (t == 1)
        {
          linha = qtd; // linha = rotas possiveis
          matriz = malloc(linha * sizeof(int *));
        } // linhas da matriz alocadas dinamicamente
        for (int p = 1; p <= n; p++)
        { // arrajos de tamanho p a n
          int k = p;
          for (int p = 0; p <= n - 1; p++)
            vetorcidades[p] = permres[p]; // atribuição de vetores
          do                              // inicio do algoritmo
          {
            int tot = 0; // soma dos totais das demandas
            for (a = 0; a < k - 1; a++)
            {
              printf("%d->", vetorcidades[a] + 1);
              tot += demanda[vetorcidades[a]];
            } // soma as demandas de cada arranjo
            printf("%d", vetorcidades[k - 1] + 1);
            tot += demanda[vetorcidades[k - 1]];
            if (tot == veichleCapacity && t == 0)
              qtd += 1; // quantidade de rotas possiveis
            else if (tot == veichleCapacity && t == 1)
            {
              for (a = 0; a < k - 1; a++)
                vetorpossivel[a] = vetorcidades[a] + 1; // insere a rota em um vetor de apoio
              vetorpossivel[a] = vetorcidades[k - 1] + 1;
              matriz[i] = malloc(coluna * sizeof(int)); // aloca colunas dinamicamente
              for (j = 0; j < coluna; j++)
              {
                matriz[i][j] = vetorpossivel[j];
              }    // insere na matriz as rotas possiveis
              i++; // iterador
            }
            count++;                          // quantidade de arranjos
            printf(" |Demanda =  %d\n", tot); // imprime a demanda de cada rota
          } while (nextPerm(vetorcidades, k, n));
        }
      }
      printf("\nNumero de arranjos: %llu\n", count); // qtd de arranjos feitos
      puts("Unicas rotas possiveis:");
      for (int k = 0; k < linha; k++)
      { // imprime a matriz de rotas possiveis
        printf("\n0 ");
        for (int f = 0; f < coluna; f++)
        {
          if (matriz[k][f] != -1)  printf("%d ", matriz[k][f]);
        }
        printf("0");
      };
      input();

#pragma endregion
      outputfile = fopen("output.txt", "a");
      struct tm *time = currentTime();
      fprintf(outputfile, "%d/%d/%d-%d:%d:%d\n", time->tm_mday, time->tm_mon, time->tm_year, time->tm_hour, time->tm_min, time->tm_sec);
      fclose(outputfile);
      input();
      break;

    default:
      break;
    }
  } while (1);

  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

int main()
{
  FILE *file, *outputfile;
  char filename[fileStringLength];
  int citiesVectorLenght;
  int veichleCapacity;
  int **distance;
  int **arr;
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
      while (fgets(buffer, fileStringLength, file))
      {
        if (nline == 0)
        { // Numero de cidades
          citiesVectorLenght = atoi(buffer);
          arr = (int **)malloc(sizeof(int *) * citiesVectorLenght + 1);
          for (int i = 0; i < citiesVectorLenght + 1; i++)
          {
            arr[i] = (int *)malloc(sizeof(int) * citiesVectorLenght + 1);
          }
          for (int i = 0; i < citiesVectorLenght + 1; i++)
          {
            for (int j = 0; j < citiesVectorLenght + 1; j++)
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
          YELLOW();
          printf("Capacidade do veiculo: %d\n", veichleCapacity);
          RESETC();
        }
        else if (nline == 2)
        {
          // demanda de cada cidade
          int i = 0;
          int demand[citiesVectorLenght];
          char *token = strtok(buffer, " ");
          while (token != NULL)
          {
            demand[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
          }
          YELLOW();
          printf("Demanda de cada cidade: ");
          for (int i = 0; i < citiesVectorLenght; i++)
          {
            printf("%d ", demand[i]);
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
      puts("distancia entre cada cidade:");
      printf("\n");
      for (int i = 0; i < citiesVectorLenght + 1; i++)
      {
        for (int j = 0; j < citiesVectorLenght + 1; j++)
        {
          printf("%d ", arr[i][j]);
        }
        printf("\n");
      }

      fclose(file);
      input();
      break;

    default:
      break;
    }
  } while (1);

  return 0;
}
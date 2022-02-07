#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "colors.c"
#ifdef WIN32
#define cls() system("cls");
#else
#define cls() system("clear");
#endif

struct tm *currentTime()
{

  time_t rawtime;
  struct tm *timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  return timeinfo;
}

void menu()
{
  CYAN();
  puts("Opcoes:");
  puts("0 - Sair");
  puts("1 - Ler arquivo de testes");
  RESETC();
}
void debug(int debugindex)
{

  RED();
  printf("Debug: %d\n", debugindex);
  RESETC();
}
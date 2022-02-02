#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <curses.h>
#elif __WIN32
#include <conio.h>
#elif __linux
#define getch getchar
#endif

#include "./src/utils/utils.c"

int main()
{
  FILE *file, *outputfile;

  do
  {
    cls();
    menu();

    char option = getch();

    switch (option)
    {
    case '0':
      return 0;
      break;

    case '1':

    default:
      break;
    }

  } while (1);

  return 0;
}
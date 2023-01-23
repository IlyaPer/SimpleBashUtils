#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN 1000

void printNonPrintable(char *str, int tabs);

int check_flags(char *str);

int main(int argc, char *argv[]) {
  FILE *fptr;
  (void)argc;

  char * str = malloc(sizeof(char) * 250);

  int line = 0;
  char *path = argv[2] != NULL ? argv[2] : argv[1];
  fptr = fopen(path, "r");
  if (fptr == NULL) {
    fprintf(stderr, "%s", "error in opening file\n");
    exit(1);
  }

  int c = 1;
  char spaces[5] = "    ";

  while (!feof(fptr) && !ferror(fptr)) {
    if (fgets(str, MAX_LEN, fptr) != NULL)
      line++;

    int num = 0;
    int dollar = 0;
    int allnum = 0;
    int squieeze = 0;
    int printNon = 0;

    if (argv[1][0] == '-') {
      switch (argv[1][1]) {
        case 'b':;
          num = 1;
          break;
        case 'e':;
          dollar = 1;
          break;
        case 'n':;
          allnum = 1;
          break;
        case 's':;
          squieeze = 1;
          break;
        case 't':;
          printNon = 1;
          break;
        default:;
          break;
      }
    }

  // for (int i = 0; i < line; i++) {
    num &&strlen(str) != 0 && data[i][0] != '\0' && data[i][0] != '\n'
        ? printf("     %d%c", c++, '\t')
        : 1;

    c == 10 || c == 100 || c == 1000 ? spaces[strlen(spaces) - 1] = '\0' : 1;
    allnum ? printf(" %s%d%c", spaces, c++, '\t') : 1;
    if (dollar) {
      if (data[i + 1][strlen(data[i]) - 1] == '\0' &&
          data[i][strlen(data[i]) - 1] != '\n') {
        printNonPrintable(data[i], 0);
        continue;
      }
      data[i][strlen(data[i]) - 1] = '\0';
      printNonPrintable(data[i], 0);
      printf("$\n");
      continue;
    }
    if (squieeze) {
      if (data[i][0] == '\n' && data[i + 1] != NULL && data[i + 1][0] == '\n')
        continue;
      printf("%s", data[i]);
      continue;
    }
    printNon ? printNonPrintable(data[i], 1) : printf("%s", data[i]);
  // }

  fclose(fptr);
}
}

int IsIn(int symbol) {
  if (10 < symbol || symbol < 160) {
    return 1;
  }
  return 0;
}

void printNonPrintable(char *str, int tabs) {
  while (str != NULL && *str != '\0') {
    switch (*str) {
      case '\t':
        if (tabs) {
          printf("^I");
          str++;
          break;
        } else
          printf("%c", '\t');
        str++;
        break;
      case '\v':
        printf("\\v");
        str++;
        break;
      case '\r':
        printf("\\r");
        str++;
        break;
      default:
        if ((*str >= 0 && *str < 9) || (*str > 10 && *str < 32)) {
          printf("^");
          *str += 64;
          printf("%c", *str);
        } else
          printf("%c", *str);
        str++;
        break;
    }
  }
}

int check_flags(char *str) {
  if ((str == NULL) || (str[0] == '\0')) return 1;
  for (int i = 1; i <= 1; i++) {
    if (str[i] == 'b' || str[i] == 's' || str[i] == 't' || str[i] == 'e' ||
        str[i] == 'n') {
      return 1;
    }
  }
  return 0;
}
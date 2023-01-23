#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search(char *flag, char *pattern);
int get_flags(int argc, char *argv[]);
int parse(char *string, char *pattern, int FLAG);
int check_flags(char *str);
void launchPrint(char *flag);
void grepPrint(char *str, char *file, int with_files, int numLines, int noData,
               int num);
void print_stuff(char *file);

void get_file_flags(char *file);

char *pat_parse(char *string, char *pattern, int FLAG, int toFind);

int lines_count(char *file, char *pattern, int advFlag, int toFind);

#define MAX_LINES 100  // malloc!
#define MAX_LEN 1000

int c = 0;
int cnt = 0;
char *files[1000];

char data[1000][1000];

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "%s", "invalid usage of grep: too few arguments\n");
    exit(1);
  } else if (argc > 2147483646) {
    fprintf(stderr, "%s", "too many arguments for grep\n");
    exit(1);
  }
  get_flags(argc, argv);
}

int get_flags(int argc, char *argv[]) {
  char *flag = malloc(sizeof(char) * 3);
  char *pattern = malloc(sizeof(char) * 100);

  for (int i = 1; i <= argc; i++) {
    if (pattern != NULL && data[cnt == 0 ? 0 : cnt - 1] != NULL &&
        data[0][0] != '\0' &&
        (i + 1 > argc || parse(argv[i + 1 < argc ? i + 1 : i], "-", 0) == 1)) {
      search(flag, pattern);
      free(flag);
      free(pattern);
      return 1;
      cnt = 0;
    }

    if (parse(argv[i], "-", 0)) {
      if (check_flags(argv[i])) {
        strcpy(flag, argv[i]);
      } else {
        fprintf(stderr, "%s", "zsh: bad pattern\n");
        exit(1);
      }
      continue;
    }

    if ((pattern == NULL || pattern[0] == '\0') && strcmp(flag, "-f")) {
      strcpy(pattern, argv[i]);
      continue;
    }
    strcpy(data[cnt++], argv[i]);
  }

  free(flag);
  free(pattern);
  return 0;
}

void search(char *flag, char *pattern) {
  int advFlag = 0;
  int toFind = 1;
  int mode = 0;
  FILE *fp;

  int lines = 0;
  int skip = 0;
  int numberLines = 0;
  int files = 0;
  int errors = 1;
  int onlyFiles = 0;
  int numFiles = 0;

  for (; flag != NULL && flag[0] != '\0'; flag++) {
    switch (*flag) {
      case 's':;
        errors = 0;
        break;
      case 'c':;
        numFiles = 1;
        break;
      case 'l':;
        onlyFiles = 1;
        break;
      case 'e':;
        advFlag = REG_EXTENDED;
        break;
      case 'o':;
        mode = 1;
        break;
      case 'h':;
        files = 1;
        break;
      case 'v':;
        toFind = 0;
        break;
      case 'f':;
        get_file_flags(data[0]);
        break;
      case 'i':;
        advFlag = REG_ICASE;
        break;
      case 'n':;
        numberLines = 1;
        break;
      default:
        break;
    }
  }

  for (int i = 0; i <= cnt - 1; i++) {
    int num = 0;
    char costil[1000];

    fp = fopen(data[i], "r");
    if (fp == NULL) {
      if (!errors) continue;
      printf("grep: %s: no such file or directory", data[i]);
      fp = NULL;
      continue;
    }

    while (!feof(fp) && !ferror(fp)) {
      if (fgets(costil, MAX_LEN, fp)) {
        if (numberLines) num++;

        if (numFiles) {
          lines = lines_count(data[i], pattern, advFlag, toFind);
          grepPrint("", data[i], files, num, onlyFiles, lines);
          numFiles = 0;
          skip = 1;
        }

        if (onlyFiles) {
          if (parse(costil, pattern, advFlag) == toFind) {
            grepPrint(costil, data[i], files, num, onlyFiles, numFiles);
            break;
          }
        }

        if (mode && !skip) {
          if (pat_parse(costil, pattern, advFlag, toFind) != NULL) {
            char *str =
                strcat(pat_parse(costil, pattern, advFlag, toFind), "\n");
            grepPrint(str, data[i], files, num, onlyFiles, numFiles);
            continue;
          }
        }

        if (parse(costil, pattern, advFlag) == toFind && !skip) {
          grepPrint(costil, data[i], files, num, onlyFiles, numFiles);
        }
      }
    }
    fclose(fp);
  }
}

int lines_count(char *file, char *pattern, int advFlag, int toFind) {
  int lines = 0;
  FILE *fp;
  char costil[1000];
  fp = fopen(file, "r");

  while (!feof(fp) && !ferror(fp)) {
    if (fgets(costil, MAX_LEN, fp)) {
      if (parse(costil, pattern, advFlag) == toFind) lines++;
    }
  }
  return lines;
}

char *pat_parse(char *string, char *pattern, int FLAG, int toFind) {
  regex_t regex;
  int reti;
  char msgbuf[100];
  regmatch_t match;

  reti = regcomp(&regex, pattern, FLAG);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  reti = regexec(&regex, string, 1, &match, 0);

  char *subbuff = malloc(sizeof(char) * 100);

  if (!reti) {
    if (toFind) {
      int i = 0;
      for (int c = match.rm_so; c < match.rm_eo; c++) {
        subbuff[i++] = string[c];
      }
      return (subbuff);
    } else
      return NULL;
  } else if (reti == REG_NOMATCH) {
    return NULL;  // 1 must be
  } else {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    exit(1);
  }
  free(subbuff);
  regfree(&regex);
  exit(1);
}

void get_file_flags(char *file) {
  FILE *fp;
  char *str = malloc(sizeof(char) * 1000);
  char costil[100];
  int flag = 0;
  fp = fopen(file, "r");

  if (fp == NULL) {
    fprintf(stderr, "Error in opening file: %s\n", file);
    return;
  }

  fclose(fp);

  strcat(str, "[");

  while (!feof(fp) && !ferror(fp)) {
    if (fgets(costil, MAX_LEN, fp)) {
      costil[strlen(costil) - 1] = '\0';
      if (*costil == '\0') strcpy(costil, "'.*'");
      if (flag) strcat(str, "\\|");
      strcat(str, costil);
      flag = 1;
    }
  }
  strcat(str, "]");

  search("-e", str);
  free(str);
  return;
}

int parse(char *string, char *pattern, int FLAG) {
  regex_t regex;
  int reti;
  char msgbuf[100];

  reti = regcomp(&regex, pattern, FLAG);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  reti = regexec(&regex, string, 0, NULL, FLAG);
  if (!reti) {
    regfree(&regex);
    return 1;
  } else if (reti == REG_NOMATCH) {
    regfree(&regex);
    return 0;
  } else {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    exit(1);
  }
  regfree(&regex);
  exit(1);

  return 1;
}

void grepPrint(char *str, char *file, int with_files, int numLines, int noData,
               int num) {
  int files = cnt > 1 && !with_files;

  if (num || str[0] == '\0') {
    printf("%d\n", num);
    return;
  }

  if (!noData) {
    files ? printf("%s:", file) : 1;
    numLines ? printf("%d:", numLines) : 1;
    str[strlen(str) - 1] != '\n' ? printf("%s\n", str) : printf("%s", str);
  } else {
    printf("%s\n", file);
    return;
  }
  return;
}

int check_flags(char *str) {
  if ((str == NULL) || (str[0] == '\0')) return 1;
  for (int i = 1; i <= 2; i++) {
    if ((str[i] == 'e' || str[i] == 'i' || str[i] == 'v' || str[i] == 'c' ||
         str[i] == 'l' || str[i] == 'n' || str[i] == 'h' || str[i] == 's' ||
         str[i] == 'f' || str[i] == 'o')) {
      return 1;
    }
  }
  return 0;
}

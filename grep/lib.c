#define _GNU_SOURCE
#include "lib.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE *fileopen(char *f_pathX, optX option) {
  struct files file;

  file.f_path = f_pathX;

  file.fn = fopen(file.f_path, "r");

  if (file.fn == NULL) {
    if (!option.s) perror(file.f_path);
    exit(1);
  }

  return file.fn;
}

void pattern_add(optX *option, char *pattern) {
  int n = strlen(pattern);
  if (option->len_arg == 0) {
    option->argument = malloc(1024 * sizeof(char));
    option->mem_arg = 1024;
  }
  if (option->mem_arg < option->len_arg + n) {
    option->argument =
        (char *)realloc((char *)(intptr_t)option->len_arg, option->mem_arg * n);
  }
  if (option->len_arg != 0) {
    strcat(option->argument + option->len_arg, "|");
    option->len_arg++;
  }
  option->len_arg +=
      sprintf(option->argument + option->len_arg, "(%s)", pattern);
}

void outline(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void print_match(regex_t *re, char *line) {
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(re, line + offset, 1, &match, 0);
    if (result != 0) break;
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void flag_f_out(FILE *fp, optX *options) {
  char *line = NULL;
  size_t memline = 0;
  int read = 0;

  if (fp != NULL)
    while (read != -1) {
      read = getline(&line, &memline, fp);
      if (line[read - 1] == '\n') line[read - 1] = '\0';
      pattern_add(options, line);
    }

  free(line);
  fclose(fp);
}

void grep_process(FILE *fp, optX *options, regex_t *reg, char *path) {
  int counter = 1;
  int Encounter = 0;
  char *line = NULL;
  size_t memline = 0;
  int read = 0;
  read = getline(&line, &memline, fp);
  if (fp != NULL)
    while (read != -1) {
      int result = regexec(reg, line, 0, NULL, 0);

      if ((result == 0 && !options->v) || (result != 0 && options->v)) {
        if (!options->c && !options->l) {
          if (!options->h) printf("%s:", path);
          if (options->n) printf("%d:", counter);
          if (options->o)
            print_match(reg, line);
          else
            outline(line, read);
        }
        Encounter++;
      }
      read = getline(&line, &memline, fp);
      counter++;
    }
  free(line);
  if (options->l && Encounter > 0) printf("%s\n", path);
  if (options->c && !options->l) {
    if (!options->h) printf("%s:", path);
    printf("%d\n", Encounter);
  }
  fclose(fp);
}
#define _GNU_SOURCE
#include "lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *fileopen(char *f_pathX, int option) {
  struct files file;

  file.f_path = f_pathX;

  switch (option) {
    case 0:
      file.fn = fopen(file.f_path, "r");
      break;
  }

  if (file.fn == NULL) printf("no such file\n");

  return file.fn;
}

char v_out(char ch) {
  if (ch == '\n' || ch == '\t') return ch;

  if (ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void outline(optX options, char *line, int n) {
  for (int i = 0; i < n; i++) {
    if (options.e && line[i] == '\n') putchar('$');
    if (options.t && line[i] == '\t') {
      line[i] = 'I';
      putchar('^');
    }
    if (options.v) line[i] = v_out(line[i]);
    putchar(line[i]);
  }
}

void output(FILE *fp, optX *options) {
  int counter = 1;
  int numb_counter = 0;
  char *line = NULL;
  size_t memline = 0;
  int read = 0;

  if (fp != NULL)
    while (read != -1) {
      read = getline(&line, &memline, fp);
      if (*line == '\n')
        numb_counter++;
      else if (*line != '\n' && numb_counter > 0)
        numb_counter = 0;
      if (options->n) printf("%6d\t", counter++);
      if (options->b && !options->n && *line != '\n')
        printf("%6d\t", counter++);

      if (options->s && numb_counter > 1) continue;

      outline(*options, line, read);
    }
  free(line);
  fclose(fp);
}

#include <stdio.h>
#include <stdlib.h>

#ifndef LIB_H
#define LIB_H

struct files {
  FILE *fn;
  char *f_path;
};
typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} optX;
char v_out(char ch);
void output(FILE *fp, optX *options);
void outline(optX options, char *line, int n);
FILE *fileopen(char *f_pathX, int option);

#endif
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef LIB_H
#define LIB_H

struct files {
  FILE *fn;
  char *f_path;
};
typedef struct {  // e:ivclnhsf:o
  int i;
  int e;
  int n;
  int s;
  int c;
  int v;
  int l;
  int h;
  int f;
  int o;
  char *argument;
  int len_arg;
  int mem_arg;
} optX;

void flag_f_out(FILE *fp, optX *options);
void outline(char *line, int n);
FILE *fileopen(char *f_pathX, optX option);
void grep_process(FILE *fp, optX *options, regex_t *reg, char *path);
void pattern_add(optX *option, char *pattern);
void print_match(regex_t *re, char *line);
#endif
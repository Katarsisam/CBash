#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

void reader(char **argv, int args, optX *option);
void parser(int args, char *argv[], optX *options);
int main(int args, char **argv) {
  optX options = {0};
  parser(args, argv, &options);
  reader(argv, args, &options);
  // free(options.argument);
  return 0;
}

void parser(int args, char *argv[], optX *options) {
  int opt;

  while ((opt = getopt(args, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        options->e = 1;
        pattern_add(options, optarg);
        break;
      case 'i':
        options->i = REG_ICASE;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->c = 1;
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        flag_f_out(fileopen(optarg, *options), options);
        break;
      case 'o':
        options->o = 1;
        break;
      default: {
        fprintf(stderr, "usag 'benstv'");
        exit(1);
      } break;
    }
  }
  if (options->argument == NULL) options->argument = argv[optind++];
  if (args - optind == 1) options->h = 1;
}

void reader(char **argv, int args, optX *options) {
  char *fpline = NULL;
  regex_t re;

  int error = regcomp(&re, options->argument, REG_EXTENDED | options->i);
  if (error) perror("Error");
  for (int i = optind; i < args; i++) {
    fpline = argv[i];
    FILE *f = fileopen(argv[i], *options);
    grep_process(f, options, &re, fpline);
  }
  regfree(&re);
}
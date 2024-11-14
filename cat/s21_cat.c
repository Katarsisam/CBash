#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

void reader(char *argv[], optX *option);
void parser(int args, char *argv[], optX *options);
int main(int args, char *argv[]) {
  optX options = {0};
  parser(args, argv, &options);
  reader(argv, &options);

  return 0;
}

void parser(int args, char *argv[], optX *options) {
  int opt;
  int option_index = 0;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};
  while ((opt = getopt_long(args, argv, "+benstvTE", long_options,
                            &option_index)) != -1)
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'e': {
        options->e = 1;
        options->v = 1;
      } break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't': {
        options->t = 1;
        options->v = 1;
      } break;
      case 'v':
        options->v = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      default: {
        fprintf(stderr, "usag 'benstv'");
        exit(1);
      } break;
    }
}

void reader(char *argv[], optX *options) {
  FILE *f = fileopen(argv[optind], 0);
  if (f != NULL) output(f, options);
}
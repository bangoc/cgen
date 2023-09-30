#include "all.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./prog out.txt 100000\n");
    return 1;
  }
  int n;
  srand(time(NULL));
  sscanf(argv[2], "%d", &n);
  FILE *out = fopen(argv[1], "w");
  fprintf(out, "%d\n", n);
  for (int i = 0; i < n; ++i) {
    fprintf(out, "%d ", rand());
    if (i % 1000 == 0) {
      fprintf(out, "\n");
    }
  }
  fclose(out);
  return 0;
}
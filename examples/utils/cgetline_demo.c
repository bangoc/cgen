#include "utils/io.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./cgetline input.txt\n");
    return 1;
  }
  FILE *inp = fopen(argv[1], "r");
  if (!inp) {
    printf("Can not open %s\n", argv[1]);
    return 1;
  }
  char *s = NULL;
  while (cgetline(&s, 0, inp)) {
    printf("%ld %s\n", (long)strlen(s), s);
  }
  fclose(inp);
  if (s) {
    free(s);
  }
  return 0;
}
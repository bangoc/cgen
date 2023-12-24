#include "all.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog 10000000\n");
    return 0;
  }
  long n;
  sscanf(argv[1], "%ld", &n);
  struct gvector *v = gvec_create(0, NULL);
  BENCH("gvec append", 1,
    for (long i = 0; i < n; ++i) {
      gvec_append(v, gtype_l(i));
    }
  );
  gvec_free(v);
  return 0;
}
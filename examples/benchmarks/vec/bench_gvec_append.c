#include "all.h"

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
  if (argc != 2) {
    printf("Usage: ./prog 10000000\n");
    return 0;
  }
  long n;
  sscanf(argv[1], "%ld", &n);
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create(0, NULL);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create(0);
#endif  // CGEN_USE_GC
  BENCH("gvec append", 1,
    for (long i = 0; i < n; ++i) {
      gvec_append(v, gtype_l(i));
    }
  );
#ifndef CGEN_USE_GC
  gvec_free(v);
#endif  // CGEN_USE_GC
  return 0;
}
#include "cgen.h"

int main() {
  struct vector *v = vcreate(0);
  vpush(v, GLONG(1));
  vpush(v, GLONG(3));
  vpush(v, GLONG(5));
  printf("%ld\n", vtop(v)->l);
  printf("%ld\n", vtop(vpop(v))->l);
  printf("%ld\n", vtop(vpop(v))->l);
  free(v);
}
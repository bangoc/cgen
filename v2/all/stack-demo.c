#include "cgen.h"

int main() {
  struct vector *v = vcreate(0);
  vpush(v, gtype_l(1));
  vpush(v, gtype_l(3));
  vpush(v, gtype_l(5));
  printf("%ld\n", vtop(v)->l);
  printf("%ld\n", vtop(vpop(v))->l);
  printf("%ld\n", vtop(vpop(v))->l);
  free(v);
}
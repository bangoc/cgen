#include "cgen.h"

int main() {
  struct vector *v = vcreate(0);
  vpush(v, gtype_l(1));
  vpush(v, gtype_l(3));
  vpush(v, gtype_l(5));
  gtype val;
  vtop(v, &val);
  printf("%ld\n", val.l);
  vtop(vpop(v), &val);
  printf("%ld\n", val.l);
  vtop(vpop(v), &val);
  printf("%ld\n", val.l);
  free(v);
}
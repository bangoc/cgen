/* (C) Nguyen Ba Ngoc 2022 */

#include "all.h"

#include "tests/base/utils.h"
#include "tests/gsl/helper.h"

int t1() {
  struct gsllist *list = gsl_create_list(NULL);
  gsl_inserta(list, NULL, gtype_l(1));
  gsl_inserta(list, NULL, gtype_l(2));
  CHECK_MSG(gsl_length(list) == 2, "Length 2");
  CHECK_MSG(gsl_sequence_g(list, (gtype[]){gtype_l(1), gtype_l(2)},
        2, gtype_cmp_l), "Sequence 1 2");
  gsl_inserta(list, gsl_front(list), gtype_l(3));
  CHECK_MSG(gsl_sequence_g(list, (gtype[]){gtype_l(1), gtype_l(3), gtype_l(2)},
        3, gtype_cmp_l), "Sequence 1 3 2");
  gsl_inserta(list, gsl_node_next(gsl_front(list)), gtype_l(5));
  gsl_inserta(list, gsl_node_next(gsl_front(list)), gtype_l(7));
  CHECK_MSG(gsl_sequence_g(list, (gtype[]){gtype_l(1), gtype_l(3), gtype_l(7),
      gtype_l(5), gtype_l(2)}, 5, gtype_cmp_l), "Sequence 1 2");
  gsl_free(list);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}
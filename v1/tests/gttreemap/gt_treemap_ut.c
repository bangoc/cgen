#include "tree/rbm.h"
#include "tests/base/utils.h"

#include <string.h>

int main() {
  struct rbmtree *t = rbm_create(gtype_cmp_s, NULL, NULL);
  char *s1 = "1111111111",
       *s2 = "2222222222",
       *s3 = "3333333333",
       *s5 = "5555555555",
       *s6 = "6666666666",
       *s7 = "7777777777",
       *sa = "Nguyen Van A",
       *sb = "Nguyen Van B",
       *sc = "Nguyen Van C",
       *sd = "Nguyen Van D",
       *se = "Nguyen Van E",
       *sf = "Nguyen Van F";
  rbm_insert(t, gtype_s(sb), gtype_s(s2));
  rbm_insert(t, gtype_s(sa), gtype_s(s1));
  rbm_insert(t, gtype_s(sc), gtype_s(s3));
  rbm_insert(t, gtype_s(sd), gtype_s(s5));
  rbm_insert(t, gtype_s(se), gtype_s(s6));
  rbm_insert(t, gtype_s(sf), gtype_s(s7));
  CHECK_MSG(strcmp(rbm_value(t, gtype_s(sa))->s, s1) == 0, "Failed A Value");
  CHECK_MSG(strcmp(rbm_value(t, gtype_s(sb))->s, s2) == 0, "Failed B Value");
  CHECK_MSG(strcmp(rbm_value(t, gtype_s(sc))->s, s3) == 0, "Failed C Value");
  CHECK_MSG(strcmp(rbm_value(t, gtype_s(sd))->s, s5) == 0, "Failed D Value");
  CHECK_MSG(strcmp(rbm_value(t, gtype_s(se))->s, s6) == 0, "Failed E Value");
  CHECK_MSG(strcmp(rbm_value(t, gtype_s(sf))->s, s7) == 0, "Failed F Value");
  CHECK_MSG(rbm_remove(t, gtype_s(sd)) == 1, "remove sd");
  CHECK_MSG(rbm_remove(t, gtype_s(se)) == 1, "remove se");
  CHECK_MSG(rbm_remove(t, gtype_s(sf)) == 1, "remove sf");
  gtype query = {.s = sd};
  CHECK_MSG(rbm_value(t, query) == NULL, "Failed not found D");
  query = gtype_s(se);
  CHECK_MSG(rbm_value(t, query) == NULL, "Failed not found E");
  query = gtype_s(sf);
  CHECK_MSG(rbm_value(t, query) == NULL, "Failed not found F");
  bn_free_tree((struct bntree *)t);
  printf("Treemap ut OK\n");
  return 0;
}

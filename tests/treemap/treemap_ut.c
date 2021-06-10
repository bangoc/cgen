#include "treemap.h"
#include "tests/base/utils.h"

#include <string.h>

int tm_compare_str(bn_node_t n1, bn_node_t n2) {
  gtype k1 = tm_key_from_bn_node(n1),
        k2 = tm_key_from_bn_node(n2);
  return strcmp(k1.s, k2.s);
}

int tm_delete_callback(treemap_node_t n) {
  free(n);
}

int main() {
  bn_tree_t t = tm_create();
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
  tm_insert(t, (gtype){.s = sa},
      (gtype){.s = s1}, tm_compare_str);
  tm_insert(t, (gtype){.s = sb},
      (gtype){.s = s2}, tm_compare_str);
  tm_insert(t, (gtype){.s = sc},
      (gtype){.s = s3}, tm_compare_str);
  tm_insert(t, (gtype){.s = sd},
      (gtype){.s = s5}, tm_compare_str);
  tm_insert(t, (gtype){.s = se},
      (gtype){.s = s6}, tm_compare_str);
  tm_insert(t, (gtype){.s = sf},
      (gtype){.s = s7}, tm_compare_str);
  CHECK_MSG(strcmp(tm_value(t, (gtype){.s = sa}, tm_compare_str).s, s1) == 0, "Failed A Value");
  CHECK_MSG(strcmp(tm_value(t, (gtype){.s = sb}, tm_compare_str).s, s2) == 0, "Failed B Value");
  CHECK_MSG(strcmp(tm_value(t, (gtype){.s = sc}, tm_compare_str).s, s3) == 0, "Failed C Value");
  CHECK_MSG(strcmp(tm_value(t, (gtype){.s = sd}, tm_compare_str).s, s5) == 0, "Failed D Value");
  CHECK_MSG(strcmp(tm_value(t, (gtype){.s = se}, tm_compare_str).s, s6) == 0, "Failed E Value");
  CHECK_MSG(strcmp(tm_value(t, (gtype){.s = sf}, tm_compare_str).s, s7) == 0, "Failed F Value");
  tm_delete(t, (gtype){.s = sd}, tm_compare_str, tm_delete_callback);
  tm_delete(t, (gtype){.s = se}, tm_compare_str, tm_delete_callback);
  tm_delete(t, (gtype){.s = sf}, tm_compare_str, tm_delete_callback);
  gtype *value = NULL_PTR;
  gtype query = {.s = sd};
  tm_value_ref(t, query, &value, tm_compare_str);
  CHECK_MSG(value == NULL_PTR, "Failed not found D");
  query = (gtype){.s = se};
  tm_value_ref(t, query, &value, tm_compare_str);
  CHECK_MSG(value == NULL_PTR, "Failed not found E");
  query = (gtype){.s = sf};
  tm_value_ref(t, query, &value, tm_compare_str);
  CHECK_MSG(value == NULL_PTR, "Failed not found F");
  treemap_node_t cur, prev = NULL_PTR;
  tm_postorder_foreach_inline(cur, t) {
    if (prev) {
      free(prev);
    }
    prev = cur;
  }
  if (prev) {
    free(prev);
  }
  free(t);
  printf("Treemap ut OK\n");
  return 0;
}
/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "tree/spec/s2i.h"
#include "utils/io.h"

#include <string.h>

rbm_t s2i_create_map(key_action_t act) {
  if (act == DUP_YES) {
    return rbm_create_map(gtype_cmp_s, gtype_free_s, NULL);
  }
  return rbm_create_map(gtype_cmp_s, NULL, NULL);
}

long *s2i_put(rbm_t si, const char *key, long value) {
  gtype gkey;
  if (bsg_tree(si)->fk) {
    gkey = gtype_s(strdup(key));
  } else {
    gkey = gtype_s(key);
  }
  gtype *res = rbm_put(si, gkey, gtype_l(value));
  if (res && bsg_tree(si)->fk) {
    bsg_tree(si)->fk(gkey);
  }
  return (long*)res;
}

long *s2i_value(rbm_t si, const char *key) {
  return (long*)rbm_value(si, gtype_s(key));
}

int s2i_remove(rbm_t si, const char *key) {
  return rbm_remove(si, gtype_s(key));
}

void s2i_print_node(bn_node_t n) {
  printf("(%s, %ld)\n", rbm_node_key(n).s, rbm_node_value(n).l);
}

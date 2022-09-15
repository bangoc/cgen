/* (C) Nguyen Ba Ngoc 2021 */

#include "tree/spec/s2i.h"
#include "utils/io.h"

#include <string.h>

struct rbmtree *s2i_create() {
  return rbm_create(gtype_cmp_s, gtype_free_s, NULL);
}

struct rbm_ires s2i_insert(struct rbmtree *si, const char *key, long value) {
  char *tmp = strdup(key);
  struct rbm_ires r = rbm_insert(si, gtype_s(tmp), gtype_l(value));
  if (!r.inserted) {
    free(tmp);
  }
  return r;
}

long *s2i_put(struct rbmtree *si, const char *key, long value) {
  char *tmp = strdup(key);
  gtype *res = rbm_put(si, gtype_s(tmp), gtype_l(value));
  if (res) {
    free(tmp);
  }
  return (long*)res;
}

long *s2i_value(struct rbmtree *si, const char *key) {
  return (long*)rbm_value(si, gtype_s(key));
}

int s2i_remove(struct rbmtree *si, const char *key) {
  return rbm_remove(si, gtype_s(key));
}

void s2i_print_node(struct bnnode *n) {
  printf("(%s, %ld)\n", rbm_node_key(n).s, rbm_node_value(n).l);
}

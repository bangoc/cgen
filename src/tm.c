#include "tm.h"

#define tm_cmp_conv(u, x) cmp(u, tm_node_key(x))

tnt tm_create_node(gtype key, gtype value) {
  tnt n = calloc(1, sizeof(struct tn_s));
  n->key = key;
  n->value = value;
  return n;
}

tnt tm_insert(tmt t, gtype key, gtype value) {
  bn_node_t same = NULL_PTR, parent = NULL_PTR;
  bn_node_t *loc;
  bn_compare_t cmp = t->cmp;
  bns_insert_setup(loc, t->t.root, key, tm_cmp_conv, same, parent);
  if (same) {
    return to_tm(same);
  }
  tnt n = tm_create_node(key, value);
  rb_insert((bn_tree_t)t, to_bn(n), loc, parent);
  return n;
}

tmt tm_create(bn_compare_t cmp) {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  tmt m = realloc(t, sizeof(struct tm_s));
  m->cmp = cmp;
  return m;
}

tnt tm_search(tmt t, gtype key) {
  bn_compare_t cmp = t->cmp;
  bns_search_inline(n, ((bn_tree_t)t), key, tm_cmp_conv, return to_tm(n));
}

gtype *tm_value(tmt t, gtype key) {
  tnt n = tm_search(t, key);
  if (n) {
    return &n->value;
  }
  return NULL;
}

tnt tm_delete(tmt t, gtype key) {
  tnt n = tm_search(t, key);
  if (n) {
    rb_delete((bn_tree_t)t, to_bn(n));
  }
  return n;
}
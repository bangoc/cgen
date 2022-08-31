#include "tree/spec/gbs.h"

/* Giao diện hỗ trợ gtype */

#include <stdlib.h>

gbs_node_t gbs_create_node(gtype key) {
  bn_node_t tmp = bn_create_node();
  gbs_node_t nn = realloc(tmp, sizeof(struct _gbs_node));
  nn->key = key;
  return nn;
}

gbs_tree_t gbs_create_tree(gbs_node_t root, gtype_cmp_t cmp, gtype_free_t fk) {
  bn_tree_t tmp = bn_create_tree(bn_node(root));
  gbs_tree_t t = realloc(tmp, sizeof(struct _gbs_tree));
  t->cmp = cmp;
  t->fk = fk;
  return t;
}

int gbs_cmp_node(bn_node_t n1, bn_node_t n2, bn_tree_t t) {
  return gbs_tree(t)->cmp(gbs_node(n1)->key, gbs_node(n2)->key);
}

bs_ires gbs_insert(gbs_tree_t t, gtype key) {
  gbs_node_t nn = gbs_create_node(key);
  return bs_insert(t, bn_node(nn), gbs_cmp_node);
}

bs_ires gbs_insert_unique(gbs_tree_t t, gtype key) {
  gbs_node_t nn = gbs_create_node(key);
  bs_ires r = bs_insert_unique(t, bn_node(nn), gbs_cmp_node);
  if (!r.inserted) {
    free(nn);
  }
  return r;
}

gbs_node_t gbs_search(gbs_tree_t t, gtype key) {
  gbs_node_s sn = {.key = key};
  return gbs_node(bs_search(bn_tree(t), bn_node(&sn), gbs_cmp_node));
}

gbs_node_t gbs_search_gte(gbs_tree_t t, gtype key) {
  gbs_node_s sn = {.key = key};
  return gbs_node(bs_search_gte(bn_tree(t), bn_node(&sn), gbs_cmp_node));
}

gbs_node_t gbs_search_lte(gbs_tree_t t, gtype key) {
  gbs_node_s sn = {.key = key};
  return gbs_node(bs_search_lte(bn_tree(t), bn_node(&sn), gbs_cmp_node));
}

int gbs_delete(gbs_tree_t t, gbs_node_t dn) {
  if (t->fk) {
    t->fk(dn->key);
  }
  return bs_delete(bn_node(t), bn_node(dn));
}

void gbs_pprint(gbs_tree_t t, gtype_print_t gpp) {
  extern int g_bn_pprint_spaces_at_begin;
  extern int g_bn_pprint_step;

#define bs_gpp(n) gpp(gbs_node(n)->key)

  bn_tree_t bnt = bn_tree(t);
  bn_pprint_inline(bnt, g_bn_pprint_spaces_at_begin, g_bn_pprint_step, bs_gpp);

#undef bs_gpp
}

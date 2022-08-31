#include "tree/spec/bsg.h"

/* Giao diện hỗ trợ gtype */

#include <stdlib.h>

bsg_node_t bsg_create_node(gtype key) {
  bn_node_t tmp = bn_create_node();
  bsg_node_t nn = realloc(tmp, sizeof(struct _bsg_node));
  nn->key = key;
  return nn;
}

bsg_tree_t bsg_create_tree(bsg_node_t root, gtype_cmp_t cmp, gtype_free_t fk) {
  bn_tree_t tmp = bn_create_tree(bn_node(root));
  bsg_tree_t t = realloc(tmp, sizeof(struct _bsg_tree));
  t->cmp = cmp;
  t->fk = fk;
  return t;
}

int bsg_node_cmp(bn_node_t n1, bn_node_t n2, bn_tree_t t) {
  return bsg_tree(t)->cmp(bsg_node(n1)->key, bsg_node(n2)->key);
}

bs_ires bsg_insert(bsg_tree_t t, gtype key) {
  bsg_node_t nn = bsg_create_node(key);
  return bs_insert(t, bn_node(nn), bsg_node_cmp);
}

bs_ires bsg_insert_unique(bsg_tree_t t, gtype key) {
  bsg_node_t nn = bsg_create_node(key);
  bs_ires r = bs_insert_unique(t, bn_node(nn), bsg_node_cmp);
  if (!r.inserted) {
    free(nn);
  }
  return r;
}

bsg_node_t bsg_search(bsg_tree_t t, gtype key) {
  bsg_node_s sn = {.key = key};
  return bsg_node(bs_search(bn_tree(t), bn_node(&sn), bsg_node_cmp));
}

bsg_node_t bsg_search_gte(bsg_tree_t t, gtype key) {
  bsg_node_s sn = {.key = key};
  return bsg_node(bs_search_gte(bn_tree(t), bn_node(&sn), bsg_node_cmp));
}

bsg_node_t bsg_search_lte(bsg_tree_t t, gtype key) {
  bsg_node_s sn = {.key = key};
  return bsg_node(bs_search_lte(bn_tree(t), bn_node(&sn), bsg_node_cmp));
}

int bsg_delete(bsg_tree_t t, bsg_node_t dn) {
  if (t->fk) {
    t->fk(dn->key);
  }
  return bs_delete(bn_node(t), bn_node(dn));
}

void bsg_pprint(bsg_tree_t t, gtype_print_t gpp) {
  extern int g_bn_pprint_spaces_at_begin;
  extern int g_bn_pprint_step;

#define bs_gpp(n) gpp(bsg_node(n)->key)

  bn_tree_t bnt = bn_tree(t);
  bn_pprint_inline(bnt, g_bn_pprint_spaces_at_begin, g_bn_pprint_step, bs_gpp);

#undef bs_gpp
}

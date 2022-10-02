#include "tree/spec/gbs.h"

/* Giao diện hỗ trợ gtype */

#include <stdlib.h>

struct gbsnode *gbs_create_node(gtype key) {
  struct bnnode *tmp = bn_create_node();
  struct gbsnode *nn = realloc(tmp, sizeof(struct gbsnode));
  nn->key = key;
  return nn;
}

struct gbstree *__gbs_create_tree(struct gbsnode *root, gtype_cmp_t cmp, gtype_free_t fk) {
  struct bntree *tmp = bn_create_tree(bn_node(root));
  struct gbstree *t = realloc(tmp, sizeof(struct gbstree));
  t->cmp = cmp;
  t->fk = fk;
  return t;
}

int gbs_cmp_node(struct bnnode *n1, struct bnnode *n2, struct bntree *t) {
  return gbs_tree(t)->cmp(gbs_node(n1)->key, gbs_node(n2)->key);
}

struct bs_ires gbs_insert(struct gbstree *t, gtype key) {
  struct gbsnode *nn = gbs_create_node(key);
  return bs_insert(t, bn_node(nn), gbs_cmp_node);
}

struct bs_ires gbs_insert_unique(struct gbstree *t, gtype key) {
  struct gbsnode *nn = gbs_create_node(key);
  struct bs_ires r = bs_insert_unique(t, bn_node(nn), gbs_cmp_node);
  if (!r.inserted) {
    free(nn);
  }
  return r;
}

struct gbsnode *gbs_search(struct gbstree *t, gtype key) {
  struct gbsnode sn = {.key = key};
  return gbs_node(bs_search(bn_tree(t), bn_node(&sn), gbs_cmp_node));
}

struct gbsnode *gbs_search_gte(struct gbstree *t, gtype key) {
  struct gbsnode sn = {.key = key};
  return gbs_node(bs_search_gte(bn_tree(t), bn_node(&sn), gbs_cmp_node));
}

struct gbsnode *gbs_search_lte(struct gbstree *t, gtype key) {
  struct gbsnode sn = {.key = key};
  return gbs_node(bs_search_lte(bn_tree(t), bn_node(&sn), gbs_cmp_node));
}

int gbs_delete(struct gbstree *t, struct gbsnode *dn) {
  if (t->fk) {
    t->fk(dn->key);
  }
  return bs_delete(t, dn);
}

void gbs_pprint(struct gbstree *t, gtype_print_t gpp) {
  extern int g_bn_pprint_spaces_at_begin;
  extern int g_bn_pprint_step;

#define bs_gpp(n) gpp(gbs_node(n)->key)

  struct bntree *bnt = bn_tree(t);
  bn_pprint_inline(bnt, g_bn_pprint_spaces_at_begin, g_bn_pprint_step, bs_gpp);

#undef bs_gpp
}

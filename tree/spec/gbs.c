#include "tree/spec/gbs.h"

/* Giao diện hỗ trợ gtype */

#include <stdlib.h>

struct gbsn *gbs_create_node(gtype key) {
  struct bnn *tmp = bn_create_node();
  struct gbsn *nn = realloc(tmp, sizeof(struct gbsn));
  nn->key = key;
  return nn;
}

struct gbst *gbs_create_tree(struct gbsn *root, gtype_cmp_t cmp, gtype_free_t fk) {
  struct bnt *tmp = bn_create_tree(bn_node(root));
  struct gbst *t = realloc(tmp, sizeof(struct gbst));
  t->cmp = cmp;
  t->fk = fk;
  return t;
}

int gbs_cmp_node(struct bnn *n1, struct bnn *n2, struct bnt *t) {
  return gbs_tree(t)->cmp(gbs_node(n1)->key, gbs_node(n2)->key);
}

struct bs_ires gbs_insert(struct gbst *t, gtype key) {
  struct gbsn *nn = gbs_create_node(key);
  return bs_insert(t, bn_node(nn), gbs_cmp_node);
}

struct bs_ires gbs_insert_unique(struct gbst *t, gtype key) {
  struct gbsn *nn = gbs_create_node(key);
  struct bs_ires r = bs_insert_unique(t, bn_node(nn), gbs_cmp_node);
  if (!r.inserted) {
    free(nn);
  }
  return r;
}

struct gbsn *gbs_search(struct gbst *t, gtype key) {
  struct gbsn sn = {.key = key};
  return gbs_node(bs_search(bn_tree(t), bn_node(&sn), gbs_cmp_node));
}

struct gbsn *gbs_search_gte(struct gbst *t, gtype key) {
  struct gbsn sn = {.key = key};
  return gbs_node(bs_search_gte(bn_tree(t), bn_node(&sn), gbs_cmp_node));
}

struct gbsn *gbs_search_lte(struct gbst *t, gtype key) {
  struct gbsn sn = {.key = key};
  return gbs_node(bs_search_lte(bn_tree(t), bn_node(&sn), gbs_cmp_node));
}

int gbs_delete(struct gbst *t, struct gbsn *dn) {
  if (t->fk) {
    t->fk(dn->key);
  }
  return bs_delete(bn_node(t), bn_node(dn));
}

void gbs_pprint(struct gbst *t, gtype_print_t gpp) {
  extern int g_bn_pprint_spaces_at_begin;
  extern int g_bn_pprint_step;

#define bs_gpp(n) gpp(gbs_node(n)->key)

  struct bnt *bnt = bn_tree(t);
  bn_pprint_inline(bnt, g_bn_pprint_spaces_at_begin, g_bn_pprint_step, bs_gpp);

#undef bs_gpp
}

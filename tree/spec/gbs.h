#ifndef SPEC_TREE_GBS_H_
#define SPEC_TREE_GBS_H_

/* (C) 2022 Nguyen Ba Ngoc (bangoc) */

#include "base/gtype.h"
#include "tree/bs.h"

struct gbsn {
  struct bnn base;
  gtype key;
};

struct gbst {
  struct bnt base;
  gtype_cmp_t cmp;
  gtype_free_t fk;
};

#define gbs_node(n) ((struct gbsn *)(n))
#define gbs_tree(t) ((struct gbst *)(t))

struct gbsn *gbs_create_node(gtype key);
int gbs_cmp_node(struct bnn *n1, struct bnn *n2, struct bnt *t);
struct gbst *gbs_create_tree(struct gbsn *root, gtype_cmp_t cmp, gtype_free_t fk);

struct bs_ires gbs_insert(struct gbst *t, gtype key);
struct bs_ires gbs_insert_unique(struct gbst *t, gtype key);
struct gbsn *gbs_search(struct gbst *t, gtype key);
struct gbsn *gbs_search_gte(struct gbst *t, gtype key);
struct gbsn *gbs_search_lte(struct gbst *t, gtype key);
int gbs_delete(struct gbst *t, struct gbsn *n);

#define gbs_free_node(n, fk) \
  do { \
    if (fk) { \
      (fk)(gbs_node(n)->key); \
    } \
    bn_free_node(n); \
  } while (0)

#define gbs_free_tree(t) \
  do { \
    if (gbs_tree(t)->fk) { \
      bn_traverse_lnr(_cur, bn_tree(t)) { \
        gbs_tree(t)->fk(gbs_node(_cur)->key); \
      }  \
    } \
    bn_free_tree(bn_tree(t)); \
  } while (0)

void gbs_pprint(struct gbst *, gtype_print_t gpp);

#endif  // SPEC_TREE_GBS_H_

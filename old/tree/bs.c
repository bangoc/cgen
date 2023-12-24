#include "tree/bs.h"

#define BS_INSERT_TPL(...) \
  struct bnnode *top = NULL; \
  struct bnnode *x = t->root; \
  int rl = 0; \
  while (x) { \
    rl = cmp(nn, x, t); \
    __VA_ARGS__ \
    top = x; \
    x = bs_child(top, rl); \
  } \
  struct bnnode * *loc = top? bs_child_ref(top, rl): &t->root; \
  bn_insert(nn, loc, top); \
  return (struct bs_ires){nn, 1}

struct bs_ires __bs_insert(struct bntree *t, struct bnnode *nn, bn_compare_t cmp) {
  BS_INSERT_TPL();
}

struct bs_ires __bs_insert_unique(struct bntree *t, struct bnnode *nn, bn_compare_t cmp) {
  BS_INSERT_TPL(
    if (!rl) {
      return (struct bs_ires){x, 0};
    }
  );
}

#undef BS_INSERT_TPL

struct bnnode *__bs_search(struct bntree *t, struct bnnode *sn, bn_compare_t cmp) {
  int rl;
  struct bnnode *x = t->root;
  while (x) {
    rl = cmp(sn, x, t);
    if (!rl) {
      return x;
    }
    x = bs_child(x, rl);
  }
  return NULL;
}

struct bnnode *__bs_search_gte(struct bntree *t, struct bnnode *sn, bn_compare_t cmp) {
  int rl;
  struct bnnode *x = t->root;
  struct bnnode *o = NULL;
  while (x) {
    rl = cmp(sn, x, t);
    if (!rl) {
      return x;
    }
    if (rl < 0) {
      o = x;
      x = x->left;
      continue;
    }
    x = x->right;
  }
  return o;
}

struct bnnode *__bs_search_lte(struct bntree *t, struct bnnode *sn, bn_compare_t cmp) {
  int rl;
  struct bnnode *x = t->root;
  struct bnnode *o = NULL;
  while (x) {
    rl = cmp(sn, x, t);
    if (!rl) {
      return x;
    }
    if (rl > 0) {
      o = x;
      x = x->right;
      continue;
    }
    x = x->left;
  }
  return o;
}

int __bs_delete(struct bntree *t, struct bnnode *dn) {
  struct bnnode *lc = dn->left,
            *rc = dn->right,
            *top = dn->top;
  if (!lc) {
    bn_change_child(dn, rc, top, t);
    if (rc) {
      bn_connect1(rc, top, top);
    }
  } else {
    if (!rc) {
      bn_change_child(dn, lc, top, t);
      bn_connect1(lc, top, top);
    } else {
      struct bnnode *successor = bn_left_most(rc);
      struct bnnode *rc2 = successor->right,
                *top2 = successor->top;
      bn_change_child(successor, rc2, top2, t);
      if (rc2) {
        bn_connect1(rc2, top, top2);
      }
      successor->left = dn->left;
      successor->right = dn->right;
      successor->top = dn->top;
      bn_change_child(dn, successor, top, t);
    }
  }
  free(dn);
  return 1;
}

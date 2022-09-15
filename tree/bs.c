#include "tree/bs.h"

#define BS_INSERT_TPL(...) \
  struct bnn *top = NULL; \
  struct bnn *x = t->root; \
  int rl = 0; \
  while (x) { \
    rl = cmp(nn, x, t); \
    __VA_ARGS__ \
    top = x; \
    x = bs_child(top, rl); \
  } \
  struct bnn * *loc = top? bs_child_ref(top, rl): &t->root; \
  bn_insert(nn, loc, top); \
  return (struct bs_ires){nn, 1}

struct bs_ires bs_insert(struct bnt *t, struct bnn *nn, bn_compare_t cmp) {
  BS_INSERT_TPL();
}

struct bs_ires bs_insert_unique(struct bnt *t, struct bnn *nn, bn_compare_t cmp) {
  BS_INSERT_TPL(
    if (!rl) {
      return (struct bs_ires){x, 0};
    }
  );
}

#undef BS_INSERT_TPL

struct bnn *bs_search(struct bnt *t, struct bnn *sn, bn_compare_t cmp) {
  int rl;
  struct bnn *x = t->root;
  while (x) {
    rl = cmp(sn, x, t);
    if (!rl) {
      return x;
    }
    x = bs_child(x, rl);
  }
  return NULL;
}

struct bnn *bs_search_gte(struct bnt *t, struct bnn *sn, bn_compare_t cmp) {
  int rl;
  struct bnn *x = t->root;
  struct bnn *o = NULL;
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

struct bnn *bs_search_lte(struct bnt *t, struct bnn *sn, bn_compare_t cmp) {
  int rl;
  struct bnn *x = t->root;
  struct bnn *o = NULL;
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

int bs_delete(struct bnt *t, struct bnn *dn) {
  struct bnn *lc = dn->left,
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
      struct bnn *successor = bn_left_most(rc);
      struct bnn *rc2 = successor->right,
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

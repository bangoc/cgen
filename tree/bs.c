#include "tree/bs.h"

#define BS_INSERT_TPL(...) \
  bn_node_t top = NULL; \
  bn_node_t x = t->root; \
  int rl = 0; \
  while (x) { \
    rl = cmp(nn, x, t); \
    __VA_ARGS__ \
    top = x; \
    x = bs_child(top, rl); \
  } \
  bn_node_t *loc = top? bs_child_ref(top, rl): &t->root; \
  bn_insert(nn, loc, top); \
  return (bs_ires){nn, 1}

bs_ires bs_insert(bn_tree_t t, bn_node_t nn, bn_compare_t cmp) {
  BS_INSERT_TPL();
}

bs_ires bs_insert_unique(bn_tree_t t, bn_node_t nn, bn_compare_t cmp) {
  BS_INSERT_TPL(
    if (!rl) {
      return (bs_ires){x, 0};
    }
  );
}

#undef BS_INSERT_TPL

bn_node_t bs_search(bn_tree_t t, bn_node_t sn, bn_compare_t cmp) {
  int rl;
  bn_node_t x = t->root;
  while (x) {
    rl = cmp(sn, x, t);
    if (!rl) {
      return x;
    }
    x = bs_child(x, rl);
  }
  return NULL;
}

bn_node_t bs_search_gte(bn_tree_t t, bn_node_t sn, bn_compare_t cmp) {
  int rl;
  bn_node_t x = t->root;
  bn_node_t o = NULL;
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

bn_node_t bs_search_lte(bn_tree_t t, bn_node_t sn, bn_compare_t cmp) {
  int rl;
  bn_node_t x = t->root;
  bn_node_t o = NULL;
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

int bs_delete(bn_tree_t t, bn_node_t dn) {
  bn_node_t lc = dn->left,
            rc = dn->right,
            top = dn->top;
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
      bn_node_t successor = bn_left_most(rc);
      bn_node_t rc2 = successor->right,
                top2 = successor->top;
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

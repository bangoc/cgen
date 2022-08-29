#include "base/bs.h"

/* Giao diện hỗ trợ gtype */

#include <stdlib.h>

bs_node_t bs_create_node(gtype key) {
  bn_node_t tmp = bn_create_node();
  bs_node_t nn = realloc(tmp, sizeof(struct _bs_node));
  nn->key = key;
  return nn;
}

bs_tree_t bs_create_tree(bs_node_t root, gtype_cmp_t cmp, gtype_free_t fk) {
  bn_tree_t tmp = bn_create_tree(bn_node(root));
  bs_tree_t t = realloc(tmp, sizeof(struct _bs_tree));
  t->cmp = cmp;
  t->fk = fk;
  return t;
}

#define BS_INSERT_TPL(...) \
  bn_tree_t bnt = bn_tree(t); \
  bn_node_t top = NULL; \
  bn_node_t x = bnt->root; \
  int rl = 0; \
  while (x) { \
    rl = t->cmp(key, bs_node(x)->key); \
    __VA_ARGS__ \
    top = x; \
    x = bs_child(top, rl); \
  } \
  bs_node_t nn = bs_create_node(key); \
  bn_node_t *loc = top? bs_child_ref(top, rl): &bnt->root; \
  bn_insert(bn_node(nn), loc, top); \
  return (bs_ires){bn_node(nn), 1}

bs_ires bs_insert(bs_tree_t t, gtype key) {
  BS_INSERT_TPL();
}

bs_ires bs_insert_unique(bs_tree_t t, gtype key) {
  BS_INSERT_TPL(
    if (!rl) {
      return (bs_ires){bn_node(x), 0};
    }
  );
}

#undef BS_INSERT_TPL

bs_node_t bs_search(bs_tree_t t, gtype key) {
  int rl;
  bn_node_t x = bn_tree(t)->root;
  while (x) {
    rl = t->cmp(key, bs_node(x)->key);
    if (!rl) {
      return bs_node(x);
    }
    x = bs_child(x, rl);
  }
  return NULL;
}

bs_node_t bs_search_gte(bs_tree_t t, gtype key) {
  int rl;
  bn_node_t x = bn_tree(t)->root;
  bn_node_t o = NULL;
  while (x) {
    rl = t->cmp(key, bs_node(x)->key);
    if (!rl) {
      return bs_node(x);
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

bs_node_t bs_search_lte(bs_tree_t t, gtype key) {
  int rl;
  bn_node_t x = bn_tree(t)->root;
  bn_node_t o = NULL;
  while (x) {
    rl = t->cmp(key, bs_node(x)->key);
    if (!rl) {
      return bs_node(x);
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

int bs_delete(bs_tree_t t, bs_node_t n) {
  bn_node_t tmp = bn_node(n);
  bn_tree_t bnt = bn_tree(t);
  bn_node_t lc = tmp->left,
            rc = tmp->right,
            top = tmp->top;
  if (!lc) {
    bn_change_child(tmp, rc, top, bnt);
    if (rc) {
      bn_connect1(rc, top, top);
    }
  } else {
    if (!rc) {
      bn_change_child(tmp, lc, top, bnt);
      bn_connect1(lc, top, top);
    } else {
      bn_node_t successor = bn_left_most(rc);
      bn_node_t rc2 = successor->right,
                top2 = successor->top;
      bn_change_child(successor, rc2, top2, bnt);
      if (rc2) {
        bn_connect1(rc2, top, top2);
      }
      successor->left = tmp->left;
      successor->right = tmp->right;
      successor->top = tmp->top;
      bn_change_child(tmp, successor, top, bnt);
    }
  }
  return 1;
}

void bs_pprint(bs_tree_t t, gtype_print_t gpp) {
  extern int g_bn_pprint_spaces_at_begin;
  extern int g_bn_pprint_step;

#define bs_gpp(n) gpp(bs_node(n)->key)

  bn_tree_t bnt = bn_tree(t);
  bn_pprint_inline(bnt, g_bn_pprint_spaces_at_begin, g_bn_pprint_step, bs_gpp);

#undef bs_gpp
}

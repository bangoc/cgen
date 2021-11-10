#include "bns.h"

/* Giao diện hỗ trợ gtype */

#include <stdlib.h>

bn_node_t bns_create_node_g(gtype key) {
  bn_node_t tmp = bn_create_node();
  bns_node_g_t nn = realloc(tmp, sizeof(struct bns_node_g));
  nn->key = key;
  return to_bn(nn);
}

bn_tree_t bns_create_tree_g(bn_node_t root, bn_compare_t cmp) {
  bn_tree_t tmp = bn_create_tree(root);
  bns_tree_g_t t = realloc(tmp, sizeof(struct bns_tree_g));
  t->cmp = cmp;
  return (bn_tree_t)t;
}

bn_node_t bns_insert_g(bn_tree_t t, gtype key) {
  bn_node_t nn = bns_create_node_g(key);
  bn_node_t top = t->root;
  bn_node_t *loc = &(t->root);
  bn_compare_t cmp = to_bns_tree_g(t)->cmp;
  while (top) {
    int order = bns_cmp_conv(key, top);
    bn_node_t tmp = bns_child(top, order);
    if (tmp) {
      top = tmp;
    } else {
      loc = bns_child_ref(top, order);
      break;
    }
  }
  bn_insert(nn, loc, top);
  return nn;
}

bn_node_t bns_search_g(bn_tree_t t, gtype key) {
  bn_compare_t cmp = to_bns_tree_g(t)->cmp;
  bns_search_inline(o, t, key, bns_cmp_conv, return o);
}

bn_node_t bns_search_gte_g(bn_tree_t t, gtype key) {
  bn_compare_t cmp = to_bns_tree_g(t)->cmp;
  bns_search_gte_inline(o, t, key, bns_cmp_conv, return o);
}

bn_node_t bns_search_lte_g(bn_tree_t t, gtype key) {
  bn_compare_t cmp = to_bns_tree_g(t)->cmp;
  bns_search_lte_inline(o, t, key, bns_cmp_conv, return o);
}

void bns_delete_g(bn_tree_t t, bn_node_t n) {
  bn_node_t lc = n->left,
            rc = n->right,
            top = n->top;
  if (!lc) {
    bn_change_child(n, rc, top, t);
    if (rc) {
      bn_connect1(rc, top, top);
    }
  } else {
    if (!rc) {
      bn_change_child(n, lc, top, t);
      bn_connect1(lc, top, top);
    } else {
      bn_node_t successor = bn_left_most(rc);
      bn_node_t rc2 = successor->right,
                top2 = successor->top;
      bn_change_child(successor, rc2, top2, t);
      if (rc2) {
        bn_connect1(rc2, top, top2);
      }
      successor->left = n->left;
      successor->right = n->right;
      successor->top = n->top;
      bn_change_child(n, successor, top, t);
    }
  }
}

void bns_pprint(bn_tree_t t, gtype_print_t gpp) {
  extern int g_bn_pprint_spaces_at_begin;
  extern int g_bn_pprint_step;
  bn_pprint_inline(t, g_bn_pprint_spaces_at_begin, g_bn_pprint_step, bns_gpp);
}
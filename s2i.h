/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef S2I_H_
#define S2I_H_

#include "rb.h"

#include <string.h>
#include <stdio.h>

typedef struct s2i_node {
  struct rb_node rb_node;
  char *key;
  long value;
} *s2i_node_t;

static int k_s2i_invalid = -1;

// ========== Khai báo hàm ===============

static s2i_node_t s2i_create_node(char *key, int value);
static s2i_node_t s2i_insert(bn_tree_t t, char *key, int value);
static s2i_node_t s2i_search(bn_tree_t t, char *key);
static int s2i_value_ref(bn_tree_t t, char *key, long **value);
static long s2i_value(bn_tree_t t, char *key);
static int s2i_delete(bn_tree_t t, char *key);
static int s2i_compare(bn_node_t x, bn_node_t y);
static void s2i_free_node(bn_node_t n);
static void s2i_free(bn_tree_t *t);
static void s2i_postorder_print(bn_tree_t tree);
static void s2i_node_print(bn_node_t n);

// ========== Macro viết nhanh ===========

#define to_s2i(n) ((s2i_node_t)n)
#define s2i_key_from_bn_node(n) to_s2i(n)->key
#define s2i_value_from_bn_node(n) to_s2i(n)->value

// ========== Định nghĩa hàm =============

static int s2i_compare(bn_node_t x, bn_node_t y) {
  char *s1 = s2i_key_from_bn_node(x);
  char *s2 = s2i_key_from_bn_node(y);
  return strcmp(s1, s2);
}

static void s2i_free_node(bn_node_t n) {
  s2i_node_t p = to_s2i(n);
  free(p->key);
  free(n);
}

static void s2i_free(bn_tree_t *tp) {
  bn_free_tree(tp, s2i_free_node);
}

static void s2i_postorder_print(bn_tree_t tree) {
  bn_node_t cur;
  bn_postorder_foreach_inline(cur, tree) {
    printf("%s: %ld\n", to_s2i(cur)->key, to_s2i(cur)->value);
  }
}

static s2i_node_t s2i_create_node(char *key, int value) {
  s2i_node_t n = malloc(sizeof(struct s2i_node));
  rb_node_init_null((&n->rb_node));
  n->key = strdup(key);
  n->value = value;
  return n;
}

static s2i_node_t s2i_insert(bn_tree_t t, char *key, int value) {
  s2i_node_t n = s2i_create_node(key, value);
  rb_insert(t, to_bn(n), s2i_compare);
  return n;
}

static s2i_node_t s2i_search(bn_tree_t t, char *key) {
  static struct s2i_node query;
  query.key = key;
  bn_node_t r = bns_search(t->root, to_bn(&query), s2i_compare);
  return to_s2i(r);
}

static int s2i_value_ref(bn_tree_t t, char *key, long **value) {
  s2i_node_t n = s2i_search(t, key);
  if (n) {
    *value = &(n->value);
    return 0;
  }
  *value = NULL_PTR;
  return 1;
}

static long s2i_value(bn_tree_t t, char *key) {
  long *value = NULL_PTR;
  s2i_value_ref(t, key, &value);
  if (value) {
    return *value;
  }
  return k_s2i_invalid;
}

static int s2i_delete(bn_tree_t t, char *key) {
  s2i_node_t n = s2i_search(t, key);
  if (n) {
    rb_delete(t, to_bn(n));
    s2i_free_node(to_bn(n));
    return 1;
  }
  return 0;
}

static void s2i_node_print(bn_node_t n) {
  s2i_node_t tmp = to_s2i(n);
  printf("(%s, %ld)\n", tmp->key, tmp->value);
}

#endif  // S2I_H_

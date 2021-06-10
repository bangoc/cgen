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
static bn_tree_t s2i_create();
static s2i_node_t s2i_insert(bn_tree_t t, char *key, int value);
static s2i_node_t s2i_search(bn_tree_t t, char *key);
static int s2i_value_ref(bn_tree_t t, char *key, long **value);
static long s2i_value(bn_tree_t t, char *key);
static int s2i_delete(bn_tree_t t, char *key);
static int s2i_compare(bn_node_t x, bn_node_t y);
static void s2i_free_node(s2i_node_t n);
static void s2i_free(bn_tree_t *t);
static void s2i_postorder_print(bn_tree_t tree);

// ========== Macro viết nhanh ===========

#define s2i_container_of(x) container_of(container_of(x, struct rb_node, bn_node), struct s2i_node, rb_node)
#define s2i_bn_node(x) &(x->rb_node.bn_node)
#define s2i_key_from_bn_node(n) ((s2i_node_t)s2i_container_of(n))->key
#define s2i_value_from_bn_node(n) ((s2i_node_t)s2i_container_of(n))->value

// ========== Định nghĩa hàm =============

static int s2i_compare(bn_node_t x, bn_node_t y) {
  char *s1 = s2i_key_from_bn_node(x);
  char *s2 = s2i_key_from_bn_node(y);
  return strcmp(s1, s2);
}

static void s2i_free_node(s2i_node_t n) {
  free(n->key);
  free(n);
}

static void s2i_free(bn_tree_t *tp) {
  bn_tree_t t = *tp;
  bn_node_t cur, prev = NULL_PTR;
  bn_postorder_foreach_inline(cur, t) {
    if (prev) {
      s2i_free_node(s2i_container_of(prev));
    }
    prev = cur;
  }
  if (prev) {
    s2i_free_node(s2i_container_of(prev));
  }
  free(t);
  *tp = NULL_PTR;
}

static void s2i_postorder_print(bn_tree_t tree) {
  bn_node_t cur;
  bn_postorder_foreach_inline(cur, tree) {
    printf("%s: %ld\n", s2i_container_of(cur)->key, s2i_container_of(cur)->value);
  }
}

static s2i_node_t s2i_create_node(char *key, int value) {
  s2i_node_t n = malloc(sizeof(struct s2i_node));
  rb_node_init((&n->rb_node), NULL_PTR, NULL_PTR, NULL_PTR, RB_BLACK);
  n->key = strdup(key);
  n->value = value;
  return n;
}

static bn_tree_t s2i_create() {
  return bn_create_tree(NULL_PTR);
}

static s2i_node_t s2i_insert(bn_tree_t t, char *key, int value) {
  s2i_node_t n = s2i_create_node(key, value);
  rb_insert(t, s2i_bn_node(n), s2i_compare);
  return n;
}

static s2i_node_t s2i_search(bn_tree_t t, char *key) {
  static struct s2i_node query;
  query.key = key;
  bn_node_t r = bns_search(t->root, s2i_bn_node((&query)), s2i_compare);
  return r? s2i_container_of(r): NULL_PTR;
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
    rb_delete(t, s2i_bn_node(n));
    s2i_free_node(n);
    return 1;
  }
  return 0;
}

#endif  // S2I_H_

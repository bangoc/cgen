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

static bn_node_t s2i_create_node(const char *key, long value);

// Lưu cặp key & value, bỏ qua nếu key đã tồn tại
static bn_node_t s2i_insert(bn_tree_t t, const char *key, long value);

// Lưu cặp key & value, cập nhật value nếu key đã tồn tại
static bn_node_t s2i_set(bn_tree_t t, const char *key, long value);

static s2i_node_t s2i_search(bn_tree_t t, const char *key);
static int s2i_value_ref(bn_tree_t t, const char *key, long **value);
static long s2i_value(bn_tree_t t, const char *key);
static int s2i_delete(bn_tree_t t, const char *key);
static int s2i_compare_data(const char *q, bn_node_t n);
static void s2i_free_node(bn_node_t n);
static void s2i_free(bn_tree_t *tp);
static void s2i_postorder_print(bn_tree_t tree);
static void s2i_print_node(bn_node_t n);

// ========== Macro viết nhanh ===========

#define to_s2i(n) ((s2i_node_t)n)
#define s2i_node_key(n) to_s2i(n)->key
#define s2i_node_value(n) to_s2i(n)->value

// ========== Định nghĩa hàm =============

static int s2i_compare_data(const char *q, bn_node_t n) {
  const char *s1 = (char*)q;
  const char *s2 = s2i_node_key(n);
  return strcmp(s1, s2);
}

static void s2i_free_node(bn_node_t n) {
  s2i_node_t p = to_s2i(n);
  free(p->key);
  free(n);
}

static void s2i_free(bn_tree_t *tp) {
  bn_tree_t t = *tp;
  bn_traverse_lnr(cur, t) {
    free(to_s2i(cur)->key);
  }
  bn_free_tree(tp);
}

static void s2i_postorder_print(bn_tree_t tree) {
  bn_node_t cur;
  bn_traverse_lrn(cur, tree) {
    printf("%s: %ld\n", to_s2i(cur)->key, to_s2i(cur)->value);
  }
}

static bn_node_t s2i_create_node(const char *key, long value) {
  s2i_node_t n = calloc(1, sizeof(struct s2i_node));
  n->key = strdup(key);
  n->value = value;
  return to_bn(n);
}

static bn_node_t s2i_insert(bn_tree_t t, const char *key, long value) {
  bn_node_t same = NULL_PTR, parent = NULL_PTR;
  bn_node_t *loc;
  bns_insert_setup(loc, t->root, key, s2i_compare_data, same, parent);
  if (same) {
    return same;
  }
  bn_node_t n = s2i_create_node(key, value);
  rb_insert(t, n, loc, parent);
  return n;
}

static bn_node_t s2i_set(bn_tree_t t, const char *key, long value) {
  bn_node_t n = s2i_insert(t, key, value);

  // TODO: Loại bỏ thao tác dư thừa trong trường hợp chưa có key
  to_s2i(n)->value = value;
  return n;
}

static s2i_node_t s2i_search(bn_tree_t t, const char *key) {
  bns_search_inline(result, t, key, s2i_compare_data, return to_s2i(result));
}

static int s2i_value_ref(bn_tree_t t, const char *key, long **value) {
  s2i_node_t n = s2i_search(t, key);
  if (n) {
    *value = &(n->value);
    return 0;
  }
  *value = NULL_PTR;
  return 1;
}

static long s2i_value(bn_tree_t t, const char *key) {
  long *value = NULL_PTR;
  s2i_value_ref(t, key, &value);
  if (value) {
    return *value;
  }
  return k_s2i_invalid;
}

static int s2i_delete(bn_tree_t t, const char *key) {
  s2i_node_t n = s2i_search(t, key);
  if (n) {
    rb_delete(t, to_bn(n));
    s2i_free_node(to_bn(n));
    return 1;
  }
  return 0;
}

static void s2i_print_node(bn_node_t n) {
  s2i_node_t tmp = to_s2i(n);
  printf("(%s, %ld) - %s\n", tmp->key, tmp->value, rb_color_str(n));
}

#endif  // S2I_H_

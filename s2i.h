/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef S2I_H_
#define S2I_H_

#include "rb.h"

#include <stdio.h>

typedef struct s2i_node {
  struct rb_node rb_node;
  char *key;
  long value;
} *s2i_node_t;

static int k_s2i_invalid = -1;

// ========== Khai báo hàm ===============

bn_node_t s2i_create_node(const char *key, long value);

// Lưu cặp key & value, bỏ qua nếu key đã tồn tại
bn_node_t s2i_insert(bn_tree_t t, const char *key, long value);

// Lưu cặp key & value, cập nhật value nếu key đã tồn tại
bn_node_t s2i_set(bn_tree_t t, const char *key, long value);

s2i_node_t s2i_search(bn_tree_t t, const char *key);
long *s2i_vref(bn_tree_t t, const char *key);
long s2i_value(bn_tree_t t, const char *key);
int s2i_delete(bn_tree_t t, const char *key);
int s2i_compare_data(const char *q, bn_node_t n);
void s2i_free_node(bn_node_t n);
void s2i_free(bn_tree_t tp);
void s2i_postorder_print(bn_tree_t tree);
void s2i_print_node(bn_node_t n);

// ========== Macro viết nhanh ===========

#define to_s2i(n) ((s2i_node_t)n)
#define s2i_node_key(n) to_s2i(n)->key
#define s2i_node_value(n) to_s2i(n)->value

#endif  // S2I_H_

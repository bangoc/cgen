/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef S2I_H_
#define S2I_H_

#include "base/rb.h"

#include <stdio.h>

typedef struct s2i_node {
  struct rb_node_s rb_node;
  char *key;
  long value;
} *s2i_node_t;

typedef struct s2i_s {
  struct bn_tree t;
  int invalid_id;
} *s2i_t;

// ========== Khai báo hàm ===============

s2i_node_t s2i_create_node(const char *key, long value);
s2i_t s2i_create();

// Lưu cặp key & value, bỏ qua nếu key đã tồn tại
s2i_node_t s2i_insert(s2i_t si, const char *key, long value);

// Lưu cặp key & value, cập nhật value nếu key đã tồn tại
s2i_node_t s2i_set(s2i_t si, const char *key, long value);

s2i_node_t s2i_search(s2i_t si, const char *key);
long *s2i_vref(s2i_t si, const char *key);
long s2i_value(s2i_t si, const char *key);
int s2i_delete(s2i_t si, const char *key);
int s2i_compare_data(const char *q, bn_node_t n);
void s2i_free_node(s2i_node_t n);
void s2i_free(s2i_t si);
void s2i_postorder_print(s2i_t tree);
void s2i_print_node(s2i_node_t n);

// ========== Macro viết nhanh ===========

#define to_s2i(n) ((s2i_node_t)n)
#define s2i_node_key(n) to_s2i(n)->key
#define s2i_node_value(n) to_s2i(n)->value

#endif  // S2I_H_

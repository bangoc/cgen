/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

/**
 * Cài đặt khái quát của cây đỏ-đen,
 * tương thích với các hàm cho cây nhị phân và cây nhị phân tìm kiếm
*/

#ifndef TREE_RB_H_
#define TREE_RB_H_

#include "tree/bs.h"

#include <stdbool.h>

/*
 * Các tính chất của cây đỏ đen:
 * 1) Mỗi nút chỉ có thể là đỏ hoặc đen
 * 2) Nút gốc là nút đen
 * 3) Tất cả các nút lá (NULL) là các nút đen
 * 4) Cả hai con của nút đỏ là các nút đen
 * 5) Tất cả các đường đi đơn giản từ nút gốc tới các nút lá đều có
 *    cùng số lượng nút đen.
 */

// đỏ = 0, đen = 1 như vậy chúng ta có tổng giá trị mầu = số lượng nút đen
typedef enum {
  RB_RED = 0,
  RB_BLACK = 1
} rb_node_color_t;

extern const char * color_names[];

typedef struct _rb_node {
  struct _bn_node base;
  rb_node_color_t color;
} rb_node_s, *rb_node_t;

#define rb_node(n) ((rb_node_t)(n))
#define rb_color(n) ((n)? rb_node(n)->color: RB_BLACK)
#define rb_color_str(n) color_names[(int)rb_color(n)]
#define rb_set_color(n, new_color) rb_node(n)->color = (new_color)
#define rb_is_red(node) (rb_color(node) == RB_RED)
#define rb_is_black(node) (rb_color(node) == RB_BLACK)
#define rb_set_black(node) rb_set_color(node, RB_BLACK)
#define rb_set_red(node) rb_set_color(node, RB_RED)

/*
  Trong triển khai này NULL được sử dụng thay vì lính canh để tương
  thích tốt hơn với các hàm ngoại.*

  Nút NULL được quy ước là nút đen
*/

rb_node_t rb_create_node();
#define rb_free_node(n) free(n)

bs_ires rb_insert(bn_tree_t t, rb_node_t nn, bn_compare_t cmp);
bs_ires rb_insert_unique(bn_tree_t t, rb_node_t nn, bn_compare_t cmp);
int rb_delete(bn_tree_t t, rb_node_t dn);

#endif  // TREE_RB_H_

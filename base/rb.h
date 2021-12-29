/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
  Cài đặt khái quát của cây đỏ-đen,
  tương thích với các hàm cho cây nhị phân và cây nhị phân tìm kiếm
*/

#ifndef RB_H_
#define RB_H_

#include "base/bn.h"
#include "base/bns.h"

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

typedef struct rb_node_s {
  struct bn_node bn_node;
  rb_node_color_t color;
} *rb_node_t;

/*
  Trong triển khai này NULL được sử dụng thay vì lính canh để tương
  thích tốt hơn với các hàm ngoại.*

  Nút NULL được quy ước là nút đen
*/

// ========== Khai báo hàm ===============

rb_node_t rb_create_node();
bn_node_t rb_insert(bn_tree_t t,
          bn_node_t node, bn_node_t *loc, bn_node_t parent);
int rb_delete(bn_tree_t t, bn_node_t z);


// ========== Macro viết nhanh ===========
#define to_rb(n) ((rb_node_t)(n))
#define rb_color(n) ((n)? to_rb(n)->color: RB_BLACK)
#define rb_color_str(n) color_names[(int)rb_color(n)]
#define rb_set_color(n, new_color) to_rb(n)->color = (new_color)
#define rb_is_red(node) (rb_color(node) == RB_RED)
#define rb_is_black(node) (rb_color(node) == RB_BLACK)
#define rb_set_black(node) rb_set_color(node, RB_BLACK)
#define rb_set_red(node) rb_set_color(node, RB_RED)

/* Xoay từ trái sang phải hoặc xoay từ phải sang trái */
/* x là trục xoay */
#define bn_rotate(t, x, right, left) \
  do { \
    bn_node_t _y = (x)->right; \
    (x)->right = _y->left; \
    if (_y->left != NULL_PTR) { \
      _y->left->top = (x); \
    } \
    _y->top = (x)->top; \
    bn_change_child(x, _y, (x)->top, t); \
    _y->left = (x); \
    (x)->top = _y; \
  } while (0)

#endif  // RB_H_

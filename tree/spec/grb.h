/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
  Cài đặt khái quát của cây đỏ-đen,
  tương thích với các hàm cho cây nhị phân và cây nhị phân tìm kiếm
*/

#ifndef TREE_SPEC_GRB_H_
#define TREE_SPEC_GRB_H_

#include "base/gtype.h"
#include "tree/rb.h"

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

extern const char * color_names[];

typedef struct _grb_node {
  struct _rb_node base;
  gtype key;
} grb_node_s, *grb_node_t;

#define grb_node(n) ((grb_node_t)(n))

/*
  Trong triển khai này NULL được sử dụng thay vì lính canh để tương
  thích tốt hơn với các hàm ngoại.*

  Nút NULL được quy ước là nút đen
*/

typedef struct _grb_tree {
  struct _bn_tree base;
  gtype_cmp_t cmp;
  gtype_free_t fk;
} grb_tree_s, *grb_tree_t;

grb_node_t grb_create_node(gtype key);
#define grb_free_node(n, t) gbs_free_node(n, gbs_tree(t)->fk)
int grb_cmp_node(bn_node_t, bn_node_t, bn_tree_t);

grb_tree_t grb_create_tree(grb_node_t root, gtype_cmp_t cmp, gtype_free_t fk);
#define grb_tree(t) ((grb_tree_t)(t))

#define grb_free_tree(t) \
  do { \
    if (grb_tree(t)->fk) { \
      bn_traverse_lnr(_cur, bn_tree(t)) { \
        grb_tree(t)->fk(grb_node(_cur)->key); \
      }  \
    } \
    bn_free_tree(bn_tree(t)); \
  } while (0)

bs_ires grb_insert(grb_tree_t t, gtype key);
bs_ires grb_insert_unique(grb_tree_t t, gtype key);
grb_node_t grb_search(grb_tree_t t, gtype key);
grb_node_t grb_search_gte(grb_tree_t t, gtype key);
grb_node_t grb_search_lte(grb_tree_t t, gtype key);
int grb_delete(grb_tree_t t, grb_node_t dn);


#endif  // TREE_SPEC_GRB_H_

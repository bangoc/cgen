/* (C) 2021 Nguyen Ba Ngoc (bangoc) */


/**
 * Cài đặt khái quát của cây đỏ-đen,
 * tương thích với các hàm cho cây nhị phân và cây nhị phân tìm kiếm
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

struct grbn {
  struct rbn base;
  gtype key;
};

/*
  Trong triển khai này NULL được sử dụng thay vì lính canh để tương
  thích tốt hơn với các hàm ngoại.*

  Nút NULL được quy ước là nút đen
*/

struct grbt {
  struct bnt base;
  gtype_cmp_t cmp;
  gtype_free_t fk;
};

#define grb_node(n) ((struct grbn *)(n))
#define grb_tree(t) ((struct grbt *)(t))

struct grbn *grb_create_node(gtype key);
#define grb_free_node(n, t) gbs_free_node(n, gbs_tree(t)->fk)
int grb_cmp_node(struct bnn *, struct bnn *, struct bnt *);

struct grbt *grb_create_tree(struct grbn *root, gtype_cmp_t cmp, gtype_free_t fk);

#define grb_free_tree(t) \
  do { \
    if (grb_tree(t)->fk) { \
      bn_traverse_lnr(_cur, bn_tree(t)) { \
        grb_tree(t)->fk(grb_node(_cur)->key); \
      }  \
    } \
    bn_free_tree(bn_tree(t)); \
  } while (0)

struct bs_ires grb_insert(struct grbt *t, gtype key);
struct bs_ires grb_insert_unique(struct grbt *t, gtype key);
struct grbn *grb_search(struct grbt *t, gtype key);
struct grbn *grb_search_gte(struct grbt *t, gtype key);
struct grbn *grb_search_lte(struct grbt *t, gtype key);
int grb_delete(struct grbt *t, struct grbn *dn);


#endif  // TREE_SPEC_GRB_H_

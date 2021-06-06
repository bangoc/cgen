/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
  Cài đặt khái quát của cây đỏ-đen,
  tương thích với các hàm cho cây nhị phân và cây nhị phân tìm kiếm
*/

#ifndef RBI_H_
#define RBI_H_

#include "bn.h"
#include "bns.h"

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

typedef enum {
  RB_BLACK,
  RB_RED
} rb_node_color_t;

typedef struct rb_node {
  struct bn_node bn_node;
  rb_node_color_t color;
} *rb_node_t;

/*
  Trong triển khai này NULL được sử dụng thay vì lính canh để tương
  thích tốt hơn với các api của cây nhị và cây nhị phân tìm kiếm.*

  Nút NULL được quy ước là nút đen
*/

// ========== Khai báo hàm ===============

static rb_node_t rb_create_node();
static bn_tree_t rb_create_tree();
static bn_tree_t rb_insert(bn_tree_t t, bn_node_t z,
                           bn_compare_t cmp);
static int rb_delete(bn_tree_t t, bn_node_t z);


// ========== Macro viết nhanh ===========

#define rb_color(x) (x? (container_of(x, struct rb_node, bn_node))->color: RB_BLACK)
#define rb_set_color(x, new_color) (container_of(x, struct rb_node, bn_node))->color = new_color
#define rb_bn_node(n) (n? ((bn_node_t)&(n->bn_node)): NULL_PTR)
#define rb_node_init(n, left_value, right_value, top_value, color_value) \
  bn_node_init(rb_bn_node(n), left_value, right_value, top_value); \
  n->color = color_value
#define rb_is_red(node) (rb_color(node) == RB_RED)
#define rb_is_black(node) (rb_color(node) == RB_BLACK)
#define rb_set_black(node) rb_set_color(node, RB_BLACK)

// ========== Định nghĩa hàm =============

static rb_node_t rb_create_node() {
  rb_node_t n = malloc(sizeof(struct rb_node));
  rb_node_init(n, NULL_PTR, NULL_PTR, NULL_PTR, RB_BLACK);
  return n;
}

static bn_tree_t rb_create_tree() {
  return bn_create_tree(NULL_PTR);
}

#define IMPL_ROTATION(t, x, left, right) \
static bn_node_t bn_ ##left ##_rotate(bn_tree_t t, bn_node_t x) { \
  bn_node_t y = x->right; \
  x->right = y->left; \
  if (y->left != NULL_PTR) { \
    y->left->top = x; \
  } \
  y->top = x->top; \
  if (x->top == NULL_PTR) { \
    t->root = y; \
  } else if (x == x->top->left) { \
    x->top->left = y; \
  } else { \
    x->top->right = y; \
  } \
  y->left = x; \
  x->top = y; \
  return y; \
}

IMPL_ROTATION(t, x, left, right)
IMPL_ROTATION(t, x, right, left)
#undef IMPL_ROTATION

static bn_tree_t rb_insert_fixup(bn_tree_t t, bn_node_t z) {
  while (rb_color(z->top) == RB_RED) {
    if (z->top == z->top->top->left) {
#define IMPL_INSERT_FIXUP(left, right) \
      bn_node_t y = z->top->top->right; \
      if (rb_color(y) == RB_RED) { \
        rb_set_color(z->top, RB_BLACK); \
        rb_set_color(y, RB_BLACK); \
        rb_set_color(z->top->top, RB_RED); \
        z = z->top->top; \
      } else { \
        if (z == z->top->right) { \
          z = z->top; \
          bn_ ##left ##_rotate(t, z); \
        } \
        rb_set_color(z->top, RB_BLACK); \
        rb_set_color(z->top->top, RB_RED); \
        bn_ ##right ##_rotate(t, z->top->top); \
      }
      IMPL_INSERT_FIXUP(left, right)
    } else {
      IMPL_INSERT_FIXUP(right, left)
    }
  }
  rb_set_color(t->root, RB_BLACK);
  return t;
}

#undef IMPL_INSERT_FIXUP

static bn_tree_t rb_insert(bn_tree_t t, bn_node_t z, bn_compare_t cmp) {
  bn_node_t y = NULL_PTR;
  bn_node_t x = t->root;
  while (x != NULL_PTR) {
    y = x;
    if (cmp(z, x) < 0) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->top = y;
  if (y == NULL_PTR) {
    t->root = z;
  } else if (cmp(z, y) < 0) {
    y->left = z;
  } else {
    y->right = z;
  }
  z->left = NULL_PTR;
  z->right = NULL_PTR;
  rb_set_color(z, RB_RED);
  rb_insert_fixup(t, z);
  return t;
}

static void rb_set_parent_color(bn_node_t n, bn_node_t parent,
                                rb_node_color_t color) {
  n->top = parent;
  rb_set_color(n, color);
}

static void rb_change_child(bn_node_t old_node, bn_node_t new_node,
                            bn_node_t parent, bn_tree_t t) {
  if (parent) {
    if (parent->left == old_node) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }
  } else {
    t->root = new_node;
  }
}

static void rb_set_parent(bn_node_t node, bn_node_t parent) {
  node->top = parent;
}

static bn_node_t rb_parent(bn_node_t node) {
  return node->top;
}

static void rb_rotate_set_parents(bn_node_t old_node,
            bn_node_t new_node, bn_tree_t t, rb_node_color_t color) {
  bn_node_t parent = rb_parent(old_node);
  rb_set_parent_color(new_node,
                      rb_parent(old_node), rb_color(old_node));
  rb_set_parent_color(old_node, new_node, color);
  rb_change_child(old_node, new_node, parent, t);
}

static bn_tree_t rb_erase_color(bn_tree_t t, bn_node_t parent) {
  bn_node_t node = NULL, sibling, tmp1, tmp2;
  while (true) {
    /*
    * Các tính chất bất biến trong vòng lặp:
    * - node là nút đen (hoặc NULL trong lần lặp đầu tiên)
    * - node không phải là nút gốc (top khác NULL_PTR)
    * - Tất cả các đường dẫn tới nút lá đi qua parent va node có số
    *   lượng nút đen ít hơn 1 so với các đường dẫn khác.
    */
    sibling = parent->right;
    if (node != sibling) {  // node == parent->left
      if (rb_is_red(sibling)) {
        /*
         * Trường hợp 1 - Xoay trái ở parent
         *
         *     P               S
         *    / \             / \
         *   N   s    -->    p   Sr
         *      / \         / \
         *     Sl  Sr      N   Sl
         */
        tmp1 = sibling->left;
        parent->right = tmp1;
        sibling->left = parent;
        rb_set_parent_color(tmp1, parent, RB_BLACK);
        rb_rotate_set_parents(parent, sibling, t, RB_RED);
        sibling = tmp1;
      }
      tmp1 = sibling->right;
      if (!tmp1 || rb_is_black(tmp1)) {
        tmp2 = sibling->left;
        if (!tmp2 || rb_is_black(tmp2)) {
          /*
           * Trường hợp 2 - Lật mầu sibling, p có thể có mầu bất kỳ
           *
           *    (p)           (p)
           *    / \           / \
           *   N   S    -->  N   s
           *      / \           / \
           *     Sl  Sr        Sl  Sr
           *
           * Điều này dẫn tới vi phạm ràng buộc 5), vi phạm này có
           * thể được khắc phục bằng cách lật mầu p thành đen nếu nó
           * là nút đỏ, hoặc đệ quy tại p. Nút p có mầu đỏ sau khi
           * xử lý trường hợp 1.
           */
          rb_set_parent_color(sibling, parent, RB_RED);
          if (rb_is_red(parent)) {
            rb_set_black(parent);
          } else {
            node = parent;
            parent = rb_parent(node);
            if (parent) {
              continue;
            }
          }
          break;
        }
        /*
         * Trường hợp 3 - Xoay phải tại sibling (p có thể có mầu bất
         * kỳ)
         *
         *   (p)           (p)
         *   / \           / \
         *  N   S    -->  N   sl
         *     / \             \
         *    sl  Sr            S
         *                       \
         *                        Sr
         * Lưu ý: p có thể là nút đỏ, và như vậy cả p và sl đều là
         * các nút đỏ sau khi xoay (vi phạm ràng buộc 4). Vấn đề này
         * được xử lý trong trường hợp 4 (trong
         * rb_rotate_set_parents() mầu của sl được thiết lập bằng
         * mầu của p và mầu của p được thiết lập bằng RB_BLACK)
         *
         *   (p)            (sl)
         *   / \            /  \
         *  N   sl   -->   P    S
         *       \        /      \
         *        S      N        Sr
         *         \
         *          Sr
         */
        tmp1 = tmp2->right;
        sibling->left = tmp1;
        tmp2->right = sibling;
        parent->right = tmp2;
        if (tmp1) {
          rb_set_parent_color(tmp1, sibling, RB_BLACK);
        }
        tmp1 = sibling;
        sibling = tmp2;
      }
      /* Trường hợp 4 - Xoay trái ở parent + lật mầu
       * (p và sl có thể có mầu bất kỳ ở đây. Sau khi xoay p có mầu
       * đen, s có mầu của p, và sl giữ mầu của nó)
       *
       *      (p)             (s)
       *      / \             / \
       *     N   S     -->   P   Sr
       *        / \         / \
       *      (sl) sr      N  (sl)
       */
      tmp2 = sibling->left;
      parent->right = tmp2;
      sibling->left = parent;
      rb_set_parent_color(tmp1, sibling, RB_BLACK);
      if (tmp2) {
        rb_set_parent(tmp2, parent);
      }
      rb_rotate_set_parents(parent, sibling, t, RB_BLACK);
      break;
    } else {
      sibling = parent->left;
      if (rb_is_red(sibling)) {
        // Trường hợp 1 - Xoay trái tại parent
        tmp1 = sibling->right;
        parent->left = tmp1;
        sibling->right = parent;
        rb_set_parent_color(tmp1, parent, RB_BLACK);
        rb_rotate_set_parents(parent, sibling, t, RB_RED);
        sibling = tmp1;
      }
      tmp1 = sibling->left;
      if (!tmp1 || rb_is_black(tmp1)) {
        tmp2 = sibling->right;
        if (!tmp2 || rb_is_black(tmp2)) {
          // Trường hợp 2 - Lật mầu sibling
          rb_set_parent_color(sibling, parent, RB_RED);
          if (rb_is_red(parent)) {
            rb_set_black(parent);
          } else {
            node = parent;
            parent = rb_parent(node);
            if (parent) {
              continue;
            }
          }
          break;
        }
        // Trường hợp 3 - Xoay trái ở sibling
        tmp1 = tmp2->left;
        sibling->right = tmp1;
        tmp2->left = sibling;
        parent->left = tmp2;
        if (tmp1) {
          rb_set_parent_color(tmp1, sibling, RB_BLACK);
        }
        tmp1 = sibling;
        sibling = tmp2;
      }
      // Trường hợp 4 - Xoay phải ở parent và lật mầu
      tmp2 = sibling->right;
      parent->left = tmp2;
      sibling->right = parent;
      rb_set_parent_color(tmp1, sibling, RB_BLACK);
      if (tmp2) {
        rb_set_parent(tmp2, parent);
      }
      rb_rotate_set_parents(parent, sibling, t, RB_BLACK);
      break;
    }
  }
  return t;
}

static int rb_erase(bn_tree_t t, bn_node_t node) {
  bn_node_t child = node->right,
            tmp = node->left,
            parent, rebalance;
  bn_node_t p;
  rb_node_color_t c;
  if (!tmp) {
    /* Trường hợp 1: Nếu nút đang xóa có không quá 1 nút con (dễ)
     *
     * Nếu có một con thì nó phải là nút đỏ do tính chất 5,
     * và node phải là nút đen theo tính chất 4. Chúng ta điều chỉnh
     * mầu trong lân cận để tránh gọi hàm sửa mầu sau này.
     */
    p = rb_parent(node);
    c = rb_color(node);
    parent = p;
    rb_change_child(node, child, parent, t);
    if (child) {
      rb_set_parent_color(child, p, c);
      rebalance = NULL_PTR;
    } else {
      rebalance = c == RB_BLACK? parent: NULL_PTR;
    }
    tmp = parent;
  } else if (!child) {
    // Vẫn trường hợp 1 nhưng nút con là node->left
    p = rb_parent(node);
    c = rb_color(node);
    rb_set_parent_color(tmp, p, c);
    parent = p;
    rb_change_child(node, tmp, parent, t);
    rebalance = NULL_PTR;
    tmp = parent;
  } else {
    bn_node_t successor = child, child2;
    tmp = child->left;
    if (!tmp) {
      /* Trường hợp 2: Nút liền sau node là con phải của node.
       *
       *    (n)          (s)
       *    / \          / \
       *  (x) (s)  ->  (x) (c)
       *        \
       *        (c)
       */
      parent = successor;
      child2 = successor->right;
    } else {
      /* Trường hợp 3: Nút liền sau node là nút trái nhất trong của
       * cây con phải của node
       *
       *    (n)          (s)
       *    / \          / \
       *  (x) (y)  ->  (x) (y)
       *      /            /
       *    (p)          (p)
       *    /            /
       *  (s)          (c)
       *    \
       *    (c)
       */
      do {
        parent = successor;
        successor = tmp;
        tmp = tmp->left;
      } while (tmp);
      child2 = successor->right;
      parent->left = child2;
      successor->right = child;
      rb_set_parent(child, successor);
    }
    tmp = node->left;
    successor->left = tmp;
    rb_set_parent(tmp, successor);
    p = rb_parent(node);
    c = rb_color(node);
    tmp = p;
    rb_change_child(node, successor, tmp, t);
    if (child2) {
      rb_set_parent_color(successor, p, c);
      rb_set_parent_color(child2, parent, RB_BLACK);
      rebalance = NULL_PTR;
    } else {
      bn_node_t p2 = rb_parent(successor);
      rb_node_color_t c2 = rb_color(successor);
      rb_set_parent_color(successor, p, c);
      rebalance = c2 == RB_BLACK? parent: NULL_PTR;
    }
    tmp = successor;
  }
  if (rebalance) {
    rb_erase_color(t, rebalance);
  }
  return 1;
}

static int rb_delete(bn_tree_t t, bn_node_t z) {
  return rb_erase(t, z);
}

#endif  // RBI_H_

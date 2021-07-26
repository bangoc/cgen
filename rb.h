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

// đỏ = 0, đen = 1 như vậy chúng ta có tổng giá trị mầu = số lượng nút đen
typedef enum {
  RB_RED = 0,
  RB_BLACK = 1
} rb_node_color_t;

static const char * color_names[] = {"Đỏ", "Đen"};

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
static bn_node_t rb_insert(bn_tree_t t, bn_node_t z,
                           bn_compare_t cmp);
static int rb_delete(bn_tree_t t, bn_node_t z);


// ========== Macro viết nhanh ===========
#define to_rb(n) ((rb_node_t)n)
#define rb_color(n) (n? to_rb(n)->color: RB_BLACK)
#define rb_color_str(n) color_names[(int)rb_color(n)]
#define rb_set_color(n, new_color) to_rb(n)->color = new_color
#define rb_node_init(n, left_value, right_value, top_value, color_value) \
  bn_node_init(to_bn(n), to_bn(left_value), to_bn(right_value), to_bn(top_value)); \
  rb_set_color(n, color_value)
#define rb_node_init_null(n) bn_node_init_null(to_bn(n)); rb_set_color(n, RB_BLACK)
#define rb_is_red(node) (rb_color(node) == RB_RED)
#define rb_is_black(node) (rb_color(node) == RB_BLACK)
#define rb_set_black(node) rb_set_color(node, RB_BLACK)
#define rb_set_red(node) rb_set_color(node, RB_RED)

// ========== Định nghĩa hàm =============

static rb_node_t rb_create_node() {
  rb_node_t n = malloc(sizeof(struct rb_node));
  rb_node_init_null(n);
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
  bn_connect2(y, left, x, top); \
  return y; \
}

IMPL_ROTATION(t, x, left, right)
IMPL_ROTATION(t, x, right, left)
#undef IMPL_ROTATION

static bn_tree_t rb_insert_fixup(bn_tree_t t, bn_node_t z) {
  bn_node_t n;
  while (rb_is_red(z->top)) {
    n = z->top;

    // z->top có mầu đỏ vì vậy z->top->top (n->top) != NULL_PTR
    if (bn_is_left(n)) {
#define IMPL_INSERT_FIXUP(left, right) \
      bn_node_t u = n->top->right; \
      if (rb_is_red(u)) { \
        rb_set_black(n); \
        rb_set_black(u); \
        rb_set_red(n->top); \
        z = n->top; \
      } else { \
        if (bn_is_ ##right(z)) { \
          bn_ ##left ##_rotate(t, n); \
          z = n; \
          n = n->top; \
        } \
        rb_set_color(n, RB_BLACK); \
        rb_set_color(n->top, RB_RED); \
        bn_ ##right ##_rotate(t, n->top); \
      }
      IMPL_INSERT_FIXUP(left, right)
    } else {
      IMPL_INSERT_FIXUP(right, left)
    }
  }
  rb_set_black(t->root);
  return t;
}

#undef IMPL_INSERT_FIXUP

static bn_node_t rb_insert_internal(bn_tree_t t,
          bn_node_t node, bn_node_t parent, int order) {
  node->top = parent;
  if (parent == NULL_PTR) {
    t->root = node;
  } else {
    bns_set_child(parent, order, node);
  }
  node->left = NULL_PTR;
  node->right = NULL_PTR;
  rb_set_red(node);
  rb_insert_fixup(t, node);
  return node;
}

static bn_node_t rb_insert(bn_tree_t t, bn_node_t node, bn_compare_t cmp) {
  bn_node_t parent = bns_can_hold(t->root, node, cmp);
  int order;
  if (parent) {
    order = cmp(node, parent);
  }
  return rb_insert_internal(t, node, parent, order);
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
  bn_node_t node = NULL, sibling,
          cn,  // Con của sibling ở phía gần node (close nephew)
          dn;  // Con của sibling ở phía xa node (distant nephew)
  while (true) {
    /*
    * Các tính chất bất biến trong vòng lặp:
    * - node là nút đen (hoặc NULL trong lần lặp đầu tiên)
    * - node không phải là nút gốc (top của nó khác NULL_PTR)
    * - Tất cả các đường dẫn tới lá đi qua parent va node có số
    *   lượng nút đen ít hơn 1 so với các đường dẫn khác.
    */
    sibling = parent->right;
    if (node != sibling) {  // node == parent->left
#define ERASE_COLOR_SYMMETRY(left, right) \
      /* Trong các ký hiệu cây chữ cái đầu viết thường là nút đỏ, \
       *    chữ cái đầu viết hoa là nút đen, \
       *    nút được để trong ngoặc có thể là đỏ hoặc đen. \
      */ \
      if (rb_is_red(sibling)) { \
        /* \
         * Trường hợp 1 - Xoay trái ở parent      \
         *                                        \
         *     P               S                  \
         *    / \             / \                 \
         *   N   s    -->    p   Dn               \
         *      / \         / \                   \
         *     Cn  Dn      N   Cn <- sibling mới  \
         */                                       \
        cn = sibling->left; \
        bn_connect2(parent, right, cn, top); \
        bn_connect1(sibling, left, parent); \
        rb_rotate_set_parents(parent, sibling, t, RB_RED); \
        sibling = cn; \
      } \
      dn = sibling->right; \
      if (!dn || rb_is_black(dn)) { \
        cn = sibling->left; \
        if (!cn || rb_is_black(cn)) { \
          /*  \
           * Trường hợp 2 - Đảo mầu sibling, p có thể có mầu bất kỳ  \
           *                                                         \
           *    (p)           (p)                                    \
           *    / \           / \                                    \
           *   N   S    -->  N   s                                   \
           *      / \           / \                                  \
           *     Cn  Dn        Cn  Dn                                \
           *                                                         \
           * Điều này dẫn tới vi phạm ràng buộc 5), vi phạm này có   \
           * thể được khắc phục bằng cách đảo mầu p thành đen nếu nó \
           * là nút đỏ, hoặc đệ quy tại p nếu ngược lại. Nút p có    \
           * mầu đỏ sau khi xử lý trường hợp 1.                      \
           */                                                        \
          rb_set_color(sibling, RB_RED); \
          if (rb_is_red(parent)) { \
            rb_set_black(parent); \
          } else { \
            node = parent; \
            parent = rb_parent(node); \
            if (parent) { \
              continue; \
            } \
          } \
          break; \
        } \
        /* \
         * Trường hợp 3 - Xoay phải tại sibling (p có thể có mầu bất \
         * kỳ)                                                       \
         *                                                           \
         *              (p)           (p)                            \
         *              / \           / \                            \
         *             N   S    -->  N   cn                          \
         *                / \             \                          \
         *               cn  Dn            S                         \
         *                                  \                        \
         *                                   Dn                      \
         * Lưu ý: + p có thể là nút đỏ, và như vậy cả p và Cn đều    \
         * là các nút đỏ sau khi xoay (vi phạm ràng buộc 4).         \
         *                                                           \
         * + Trong triển khai này chúng ta chỉ thực hiện một phần    \
         * các thao tác xoay phải tại sibling, vì vậy sau khi xử lý  \
         * trường hợp 3 đường đi từ p qua cn sau đó rẽ về phía N bị  \
         * giảm một nút đen (S, vi phạm tính chất 5).                \
         *                                                           \
         * Các vấn đề  này được xử lý trong trường hợp 4 (trong      \
         * rb_rotate_set_parents() - cn được tô bằng mầu của p       \
         * và p được tô mầu đen)                                     \
         *                                                           \
         *   (p)            (cn)                                     \
         *   / \            /  \                                     \
         *  N   cn   -->   P    S                                    \
         *       \        /      \                                   \
         *        S      N        Dn                                 \
         *         \                                                 \
         *          Dn                                               \
         */                                                          \
        bn_node_t tmp = cn->right; \
        bn_connect2(cn, right, sibling, top); \
        parent->right = cn; \
        sibling->left = tmp; \
        if (tmp) { \
          bn_connect1(tmp, top, sibling); \
        } \
        dn = sibling; \
        sibling = cn; \
      } \
      /* Trường hợp 4 - Xoay trái ở parent + đảo mầu                 \
       * (p và cn có thể có mầu bất kỳ ở đây. Sau khi xoay p có mầu  \
       * đen, s có mầu của p, và cn giữ mầu của nó)                  \
       *                                                             \
       *      (p)             (s)                                    \
       *      / \             / \                                    \
       *     N   S     -->   P   Dn                                  \
       *        / \         / \                                      \
       *      (cn) dn      N  (cn)                                   \
       */                                                            \
      cn = sibling->left; \
      parent->right = cn; \
      sibling->left = parent; \
      rb_set_color(dn, RB_BLACK); \
      if (cn) { \
        rb_set_parent(cn, parent); \
      } \
      rb_rotate_set_parents(parent, sibling, t, RB_BLACK); \
      break
      ERASE_COLOR_SYMMETRY(left, right);
    } else {
      sibling = parent->left;
      ERASE_COLOR_SYMMETRY(right, left);
#undef ERASE_COLOR_SYMMETRY
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
     * Nếu có một con thì nút con phải là nút đỏ do tính chất 5,
     * và nó phải là nút đen theo tính chất 4. Chúng ta điều chỉnh
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
      /* Trường hợp 3: Nút liền sau node là nút trái nhất trong
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
      rb_set_parent_color(child2, parent, RB_BLACK);
      rebalance = NULL_PTR;
    } else {
      rb_node_color_t c2 = rb_color(successor);
      rebalance = c2 == RB_BLACK? parent: NULL_PTR;
    }
    rb_set_parent_color(successor, p, c);
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

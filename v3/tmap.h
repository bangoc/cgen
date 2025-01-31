/* (C) Nguyễn Bá Ngọc 2023-2025 */

#ifndef TMAP_H_
#define TMAP_H_

#include "tnav.h"

#include <stddef.h>

enum tmap_node_colors {
  RED = 0,
  BLACK = 1
};

#define COLOR(n) ((n)? (n)->color: BLACK)
#define IS_RED(n) ((n) && (n)->color == RED)
#define IS_BLACK(n) (!(n) || (n)->color == BLACK)
#define PAINT_BLACK(n) (n)->color = BLACK
#define PAINT_RED(n) (n)->color = RED
#define PAINT(n, c) (n)->color = (c)

#define TMAP_DECL(tname, key_t, value_t) \
struct tname##_node; \
struct tname; \
struct tname *tname(int (*cmp)(const key_t key1, const key_t key2), \
                    void (*fk)(), void (*fv)()); \
void tname##_free(struct tname *tm); \
struct tname##_node *tname##_put(struct tname *tm, key_t key, value_t value); \
struct tname##_node *tname##_get(struct tname *tm, key_t key); \
int tname##_rem(struct tname *tm, key_t key); \
TNAV_DECL(tname)

#define TMAP_FNODE(tm, n) \
{ \
  if (tm->fk) { \
    tm->fk(n->key); \
  } \
  if (tm->fv) { \
    tm->fv(n->value); \
  } \
  free(n); \
}

#define TMAP_IMPL(tname, key_t, value_t) \
struct tname##_node { \
  key_t key; \
  value_t value; \
  enum tmap_node_colors color; \
  struct tname##_node *left; \
  struct tname##_node *right; \
  struct tname##_node *top; \
}; \
struct tname { \
  struct tname##_node *root; \
  int (*cmp)(const key_t key1, const key_t key2); \
  void (*fk)(); \
  void (*fv)(); \
  long size; \
}; \
static inline void tname##_change(struct tname *tm, struct tname##_node *old_node, \
        struct tname##_node *new_node) { \
  struct tname##_node *top = old_node->top; \
  if (top) { \
    if (top->left == old_node) { \
      top->left = new_node; \
    } else { \
      top->right = new_node; \
    } \
  } else { \
    tm->root = new_node; \
  } \
  if (new_node) { \
    (new_node)->top = top; \
  } \
} \
/*       x                                r
      l     r <- y                    x       z
          rl  z                     l   rl
*/ \
static inline void tname##_rotate_left(struct tname *tm, struct tname##_node *x) { \
  struct tname##_node *y = x->right; \
  x->right = y->left; \
  if (y->left != NULL) { \
    y->left->top = x; \
  } \
  tname##_change(tm, x, y); \
  y->left = x; \
  x->top = y; \
}\
/*       x                      l
   y->l     r               z       x
    z   lr                        lr  r
*/ \
static inline void tname##_rotate_right(struct tname *tm, struct tname##_node *x) { \
  struct tname##_node *y = x->left; \
  x->left = y->right; \
  if (y->right != NULL) { \
    y->right->top = x; \
  } \
  tname##_change(tm, x, y); \
  y->right = x; \
  x->top = y; \
}\
static inline void tname##_put_fixup(struct tname *tm, struct tname##_node *n) {\
  /*
   * Các biến:
   * tm - con trỏ tới bảng cây (tree map)
   * n  - ban đầu là nút mới được thêm vào (node)
   * t  - là đỉnh của n (n->top)
   * s  - nút đứng cạnh t trong cây (side)
   * tt - là đỉnh của t (t->top)
   *
   * Trong các sơ đồ minh họa cây thì nút có tên được viết hoa là nút đen,
   *    nút có tên viết thường là nút đỏ, nút được đặt trong dấu () có thể
   *    là nút đen hoặc nút đỏ (không ảnh hưởng đển tính đúng đắn).
   */ \
  struct tname##_node *t = n->top, *tt = t->top; \
  /* Các bất biến của vòng lặp:
   *  + t là đỉnh của n, tính chất cây đỏ đen chỉ bị vi phạm ở đoạn
   *    t-n: t và n là các nút đỏ (tính chất 4). Vấn đề này được
   *    khắc phục trong quá trình n được đẩy lên phía gốc.
   * Ban đầu n là nút mới được thêm vào, sau mỗi vòng lặp n tiến
   * gần hơn về phía gốc của cây. Vòng lặp dừng lại khi t ==
   * NULL (n là gốc của cây) hoặc t được tô mầu đen.
   *
   * Trong vòng lặp chúng ta có
   *  + n->top != NULL và t->top != NULL (vì n và t là các nút đỏ)
   */ \
  while (1) { \
    if (t == tt->left) { \
      /* t thuộc nhánh trái của tt - đối xứng với tường hợp t thuộc nhánh phải */ \
      if (IS_RED(tt->right)) { \
        /*Nếu s là nút đỏ => Đảo mầu t và s thành các nút đen, TT thành nút đỏ.
               TT                tt  <- n mới
             t   s  thành>>>   T    S
          ->n <-                n mới có thể vi phạm tính chất 4 nếu tt->top là đỏ,
                                có thể là con trái hoặc con phải trong cây.
         */ \
        PAINT_BLACK(t); \
        PAINT_BLACK(tt->right); \
        PAINT_RED(tt); \
        n = tt; \
        t = n->top; \
        if (t == NULL) { \
          /* n là gốc của cây */ \
          PAINT_BLACK(n); \
          break; \
        } \
        tt = t->top; \
        if (IS_BLACK(t)) { \
          /* Đã thỏa mãn các tính chất */ \
          break; \
        } \
      } else { \
        /* Trường hợp s là nút đen */ \
        if (n == t->right) { \
          /* Nếu n thuộc nhánh phải của t thì xoay trái tại t
                 TT                  TT
               t    S  thành>>>   n <-t  S
                n               t  <-n mới
           */ \
          tname##_rotate_## left(tm, t); \
          n = t; \
          t = n->top; \
        } \
        /* Trường hợp n thuộc nhánh trái của t => Đảo mầu TT thành đỏ và t thành đen,
                TT                   tt
             t     S  đảo mầu >>   T   S
           n                      n
          Các tính chất được thỏa mãn sau khi xoay phải ở TT.
              T
            n    tt
                    S
         */ \
        PAINT_BLACK(t); \
        PAINT_RED(tt); \
        tname##_rotate_## right(tm, tt); \
        break;  \
      } \
    } else { \
      /* Đối xứng với trường hợp t thuộc nhánh trái */ \
      if (IS_RED(tt->left)) { \
        PAINT_BLACK(t); \
        PAINT_BLACK(tt->left); \
        PAINT_RED(tt); \
        n = tt; \
        t = n->top; \
        if (t == NULL) { \
          PAINT_BLACK(n); \
          break; \
        } \
        tt = t->top; \
        if (IS_BLACK(t)) { \
          break; \
        } \
      } else { \
        if (n == t->left) { \
          tname##_rotate_## right(tm, t); \
          n = t; \
          t = n->top; \
          tt = t->top; \
        } \
        PAINT_BLACK(t); \
        PAINT_RED(tt); \
        tname##_rotate_## left(tm, tt); \
        break;  \
      } \
    } \
  } \
}\
static inline void tname##_detach_node_fixup(struct tname *tm, struct tname##_node* t) {\
  /* n - nút, s - nút cạnh n (side), cn - nút dưới phía gần n (close node),
   * dn - nút dưới phía xa n (distant node) */\
  struct tname##_node *n = NULL, *s, *cn, *dn; \
  /*
   * Các tính chất bất biến trong vòng lặp:
   * - n là nút đen (== NULL trong lần lặp đầu tiên)
   * - n không phải là nút gốc (đỉnh của nó khác NULL)
   * - Tất cả các đường dẫn tới lá đi qua t và n có số
   *   lượng nút đen ít hơn 1 so với các đường dẫn khác (vi phạm tính chất 5).
   */ \
  /* Trong các sơ đồ cây nút viết hoa là nút đen,
   * nút viết thường là nút đỏ, nút trong ngoặc có thể là đỏ hoặc đen.
   */ \
  while (1) { \
    s = t->right; \
    if (n != s) { \
      /* Kịch bản n thuộc nhánh trái của t - đối xứng với trường hợp
       * n thuộc nhánh phải */ \
      if (IS_RED(s)) { \
        /* Trường hợp 1, s là nút đỏ (vì vậy T, CN, DN là các nút đen)
         * => Xoay trái ở t, tô t thành đỏ và S thành đen.
         *
         *     T               S
         *    / \             / \
         *   N   s    -->    t   DN
         *      / \         / \
         *     CN  DN      N   CN <- s mới
         */ \
        tname##_rotate_## left(tm, t); \
        PAINT_RED(t); \
        PAINT_BLACK(s); \
        s = t->right; \
      } \
      dn = s->right; \
      if (IS_BLACK(dn)) { \
        cn = s->left; \
        if (IS_BLACK(cn)) { \
          /*
           * Trường hợp 2, S, DN và CN là các nút đen, (t) có thể
           * có mầu bất kỳ (có mầu đỏ sau khi xử lý trường hợp 1)
           * => Tô s thành đỏ.
           *
           *    (t)            T  <- n mới (nếu (t) là nút đen có đỉnh).
           *    / \           / \
           *   N   S    -->  N   s
           *      / \           / \
           *     CN  DN        CN  DN
           *
           * Nếu t là nút đỏ thì có thể khắc phục vi phạm ràng buộc 5
           * bằng cách tô t thành đen, nếu ngược lại, nếu t là gốc cây
           * thì các tính chất đỏ đen đã được đáp ứng, nếu t có đỉnh
           * thì lặp lại với t là n mới.
           */ \
          PAINT_RED(s); \
          if (IS_RED(t)) { \
            PAINT_BLACK(t); \
            break; \
          } \
          n = t; \
          t = n->top; \
          if (t) { \
            continue; \
          } else { \
            break; \
          } \
        } \
        /*
         * Trường hợp 3, S, DN đen, cn đỏ, (t) có thể có mầu bất kỳ
         * => Xoay phải tại s
         *
         *              (t)           (t)
         *              / \           / \
         *             N   S    -->  N   cn
         *                / \             \
         *               cn  DN            S
         *                                  \
         *                                   DN
         * Nếu t là nút đỏ thì cả t và cn đều là các nút đỏ sau khi xoay
         * (vi phạm ràng buộc 4).
         */ \
        tname##_rotate_## right(tm, s); \
        /*
         * + Đường đi từ t qua cn sau đó rẽ về phía N  bị giảm 1
         * nút đen (S) (vi phạm tính chất 5).
         *
         * Các vấn đề này được xử lý bằng cách xoay trái tại t
         * Sau đó tô cn bằng mầu cũ của (t), tô (t) thành đen
         *
         *   (t)                 (cn)
         *   / \     -->         /  \
         *  N   cn              T    S
         *       \             /      \
         *        S           N        DN
         *         \
         *          DN
         */ \
        tname##_rotate_ ##left(tm, t); \
        PAINT(cn, t->color); \
        PAINT_BLACK(t); \
        break; \
      } \
      /* Trường hợp 4 - S là nút đen, dn là nút đỏ, (t) và (cn) có thể có mầu bất kỳ
       * => Xoay trái ở t, tô s bằng mầu cũ của t, còn t và dn được tô mầu đen.
       *
       *      (t)             (s)
       *      / \             / \
       *     N   S     -->   T   DN
       *        / \         / \
       *      (cn) dn      N  (cn)
       */ \
      dn = s->right; \
      tname##_rotate_ ##left(tm, t); \
      PAINT(s, t->color); \
      PAINT_BLACK(t); \
      PAINT_BLACK(dn); \
      break; \
    } else { \
      /* Đối xứng với trường hợp n là con trái của t */ \
      s = t->left; \
      if (IS_RED(s)) { \
        tname##_rotate_## right(tm, t); \
        PAINT_RED(t); \
        PAINT_BLACK(s); \
        s = t->left; \
      } \
      dn = s->left; \
      if (IS_BLACK(dn)) { \
        cn = s->right; \
        if (IS_BLACK(cn)) { \
          PAINT_RED(s); \
          if (IS_RED(t)) { \
            PAINT_BLACK(t); \
          } else { \
            n = t; \
            t = n->top; \
            if (t) { \
              continue; \
            } \
          } \
          break; \
        } \
        tname##_rotate_## left(tm, s); \
        s = t->left; \
      } \
      dn = s->left; \
      tname##_rotate_ ##right(tm, t); \
      PAINT(s, t->color); \
      PAINT_BLACK(t); \
      PAINT_BLACK(dn); \
      break; \
    } \
  } \
}\
struct tname##_node *tname##_node(key_t key, value_t value) { \
  struct tname##_node *nn = malloc(sizeof(struct tname##_node)); \
  nn->key = key; \
  nn->value = value; \
  PAINT_RED(nn); \
  nn->left = nn->right = nn->top = NULL; \
  return nn; \
} \
struct tname *tname(int (*cmp)(const key_t key1, const key_t key2), \
                    void (*fk)(), void (*fv)()) { \
  if (!cmp) { \
    return NULL; \
  } \
  struct tname *tm = malloc(sizeof(struct tname)); \
  tm->root = NULL; \
  tm->cmp = cmp; \
  tm->fk = fk; \
  tm->fv = fv; \
  tm->size = 0; \
  return tm; \
} \
void tname##_free(struct tname *tm) { \
  struct tname##_node *n = tname##_first_lrn(tm); \
  struct tname##_node *tmp = NULL; \
  while (n) { \
    tmp = n; \
    n = tname##_next_lrn(n); \
    TMAP_FNODE(tm, tmp) \
  } \
  tm->size = 0; \
  free(tm); \
} \
static void tname##_detach_node(struct tname *tm, struct tname##_node *dn) { \
  struct tname##_node *node = dn; \
  struct tname##_node *child = node->right, \
            *tmp = node->left, \
            *top, *rebalance; \
  /* Trường hợp 1: Nếu nút đang xóa có không quá 1 nút con (dễ)
   *
   * Nếu chỉ có 1 con thì nút con phải là nút đỏ do tính chất 5,
   * và nó phải là nút đen theo tính chất 4. Có thể điều chỉnh
   * mầu trong lân cận để giữ các tính chất cây đỏ-dên.
   */ \
  if (!tmp) { \
    tname##_change(tm, node, child); \
    if (child) { \
      /* node phải là nút đen và child phải là nút đỏ */ \
      PAINT_BLACK(child); \
      rebalance = NULL; \
    } else { \
      /* Cả 2 con của node đều là NULL => Vị trí cũ của node
       * được thay bằng con trỏ NULL. Nếu node là nút đen thì
       * độ cao đen của đường đi qua node giảm 1 => vi phạm tính chất 5. */ \
      rebalance = IS_BLACK(node)? node->top: NULL; \
    } \
  } else if (!child) { \
    /* node phải là nút đen và tmp là nút đỏ */ \
    tname##_change(tm, node, tmp); \
    PAINT_BLACK(tmp); \
    rebalance = NULL; \
  } else { \
    struct tname##_node *sss = child, *child2; \
    tmp = child->left; \
    if (!tmp) { \
      /* Trường hợp 2: Nút liền sau node (sss - successor) là con phải của node.
       *
       *    (n)          (s)
       *    / \          / \
       *  (x) (s)  ->  (x) (c2)
       *        \
       *        (c2)
       */ \
      top = sss; \
      child2 = sss->right; \
    } else { \
      /* Trường hợp 3: Con phải của node có con trái.
       *
       *    (n)          (s)
       *    / \          / \
       *  (x) (y)  ->  (x) (y)
       *      /            /
       *    (t)          (t)
       *    /            /
       *  (s)          (c2)
       *    \
       *    (c2)
       */ \
      do { \
        sss = tmp; \
        tmp = tmp->left; \
      } while (tmp); \
      top = sss->top; \
      child2 = sss->right; \
      top->left = child2; \
      if (child2) { \
        child2->top = top; \
      } \
      sss->right = child; \
      child->top = sss; \
    } \
    /* Cấy sss vào vị trí của node cho cả trường hợp 2 và 3 */ \
    tmp = node->left; \
    sss->left = tmp; \
    tmp->top = sss; \
    if (child2) { \
      /* child2 phải là nút đỏ và top của nó phải là nút đen do top của nó
       * không có con trái */ \
      PAINT_BLACK(child2); \
      rebalance = NULL; \
    } else {\
      /* child2 == NULL => Vị trí cũ của sss được thay bằng NULL,
       * Nếu sss là nút đen thì độ cao đen của đường đi qua child2
       * bị giảm 1 => vi phạm tính chất 5 */ \
      rebalance = IS_BLACK(sss) ? top: NULL; \
    }\
    tname##_change(tm, node, sss); \
    PAINT(sss, node->color); \
  } \
  if (rebalance) { \
    /* Nút rebalance có 1 con NULL sao cho đường đi qua đó
     * ngắn hơn 1 so với các đường đi khác */ \
    tname##_detach_node_fixup(tm, rebalance); \
  } \
  --(tm->size); \
} \
struct tname##_node *tname##_put(struct tname *tm, key_t key, value_t value) { \
  struct tname##_node *top = NULL, *x = tm->root, **loc = &tm->root; \
  int rl = 0; \
  while (x) { \
    rl = tm->cmp(key, x->key); \
    if (rl == 0) { \
      return x; \
    } \
    top = x; \
    if (rl < 0) { \
      x = top->left; \
      loc = &top->left; \
    } else { \
      x = top->right; \
      loc = &top->right; \
    } \
  } \
  struct tname##_node *nn = tname##_node(key, value); \
  *loc = nn; \
  nn->top = top; \
  if (top == NULL) { \
    nn->color = BLACK; \
  } else if (IS_RED(top)) { \
    /* Vi phạm tính chất 4 (sau thao tác thêm vào chỉ có tính chất 4
       có thể bị vi phạm). */ \
    tname##_put_fixup(tm, nn); \
  } \
  ++tm->size; \
  return NULL; \
} \
struct tname##_node *tname##_get(struct tname *tm, key_t key) { \
  struct tname##_node *x = tm->root; \
  while (x) { \
    int rl = tm->cmp(key, x->key); \
    if (rl == 0) { \
      break; \
    } \
    x = rl < 0? x->left: x->right; \
  } \
  if (!x) { \
    return NULL; \
  } \
  return x; \
} \
int tname##_rem(struct tname *tm, key_t key) { \
  struct tname##_node *n = tname##_get(tm, key); \
  if (!n) { \
    return 0; \
  } \
  tname##_detach_node(tm, n);\
  TMAP_FNODE(tm, n) \
  return 1; \
} \
TNAV_IMPL(tname)


#define TMAP_DECL_IMPL(tname, keytype, valtype) \
TMAP_DECL(tname, keytype, valtype); \
TMAP_IMPL(tname, keytype, valtype)

#endif  // TMAP_H_

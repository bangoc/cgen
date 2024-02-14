/* (C) Nguyễn Bá Ngọc 2023 */

#ifndef CONT_TMAP_H_
#define CONT_TMAP_H_

#include <stddef.h>

enum tcolors {
  RED = 0,
  BLACK = 1
};

#define TNN(tname) tname##_node

#define TDEFN(tname, ktype, vtype) \
struct TNN(tname) { \
  ktype key; \
  vtype value; \
  enum tcolors color; \
  struct TNN(tname) *left; \
  struct TNN(tname) *right; \
  struct TNN(tname) *top; \
}; \
struct tname { \
  struct TNN(tname) *root; \
  compare_fnt cmp; \
  void (*fk)(ktype);\
  void (*fv)(vtype); \
  long size; \
}

#define TCOLOR(n) ((n)? (n)->color: BLACK)
#define TIS_RED(n) ((n) && (n)->color == RED)
#define TIS_BLACK(n) (!(n) || (n)->color == BLACK)
#define TPAINT_BLACK(n) (n)->color = BLACK
#define TPAINT_RED(n) (n)->color = RED
#define TPAINT(n, c) (n)->color = (c)

#define TDECL(tname, ktype, vtype, prefix) \
TDEFN(tname, ktype, vtype); \
struct TNN(tname) *prefix##left_most(struct TNN(tname) *n); \
struct TNN(tname) *prefix##right_most(struct TNN(tname) *n); \
struct TNN(tname) *prefix##left_deepest(struct TNN(tname) *n); \
struct TNN(tname) *prefix##next_lrn(struct TNN(tname) *n); \
struct TNN(tname) *prefix##next_lnr(struct TNN(tname) *n); \
struct TNN(tname) *prefix##prev_lnr(struct TNN(tname) *n); \
struct TNN(tname) *prefix##first_lrn(struct tname *tm); \
struct TNN(tname) *prefix##first_lnr(struct tname *tm); \
struct TNN(tname) *prefix##last_lnr(struct tname *tm); \
struct TNN(tname) *prefix##pval_node(void *pv); \
struct tname *prefix##create(compare_fnt cmp); \
struct tname *tname(compare_fnt cmp); \
void prefix##clear(struct tname *tm); \
void prefix##free(struct tname *tm); \
vtype *prefix##put(struct tname *tm, ktype key, vtype value); \
vtype *prefix##get(struct tname *tm, ktype key); \
struct tname *prefix##remove(struct tname *tm, ktype key)

#define TIMPL(tname, ktype, vtype, prefix) \
static inline void prefix##change(struct tname *tm, struct TNN(tname) *old_node, \
        struct TNN(tname) *new_node) { \
  struct TNN(tname) *top = old_node->top; \
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
static inline void prefix##rotate_left(struct tname *tm, struct TNN(tname) *x) { \
  struct TNN(tname) *y = x->right; \
  x->right = y->left; \
  if (y->left != NULL) { \
    y->left->top = x; \
  } \
  prefix##change(tm, x, y); \
  y->left = x; \
  x->top = y; \
}\
/*       x                      l
   y->l     r               z       x
    z   lr                        lr  r
*/ \
static inline void prefix##rotate_right(struct tname *tm, struct TNN(tname) *x) { \
  struct TNN(tname) *y = x->left; \
  x->left = y->right; \
  if (y->right != NULL) { \
    y->right->top = x; \
  } \
  prefix##change(tm, x, y); \
  y->right = x; \
  x->top = y; \
}\
static inline void prefix##put_fixup(struct tname *tm, struct TNN(tname) *n) {\
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
  struct TNN(tname) *t = n->top, *tt = t->top; \
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
      if (TIS_RED(tt->right)) { \
        /*Nếu s là nút đỏ => Đảo mầu t và s thành các nút đen, TT thành nút đỏ.
               TT                tt  <- n mới
             t   s  thành>>>   T    S
          ->n <-                n mới có thể vi phạm tính chất 4 nếu tt->top là đỏ,
                                có thể là con trái hoặc con phải trong cây.
         */ \
        TPAINT_BLACK(t); \
        TPAINT_BLACK(tt->right); \
        TPAINT_RED(tt); \
        n = tt; \
        t = n->top; \
        if (t == NULL) { \
          /* n là gốc của cây */ \
          TPAINT_BLACK(n); \
          break; \
        } \
        tt = t->top; \
        if (TIS_BLACK(t)) { \
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
          prefix##rotate_## left(tm, t); \
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
        TPAINT_BLACK(t); \
        TPAINT_RED(tt); \
        prefix##rotate_## right(tm, tt); \
        break;  \
      } \
    } else { \
      /* Đối xứng với trường hợp t thuộc nhánh trái */ \
      if (TIS_RED(tt->left)) { \
        TPAINT_BLACK(t); \
        TPAINT_BLACK(tt->left); \
        TPAINT_RED(tt); \
        n = tt; \
        t = n->top; \
        if (t == NULL) { \
          TPAINT_BLACK(n); \
          break; \
        } \
        tt = t->top; \
        if (TIS_BLACK(t)) { \
          break; \
        } \
      } else { \
        if (n == t->left) { \
          prefix##rotate_## right(tm, t); \
          n = t; \
          t = n->top; \
          tt = t->top; \
        } \
        TPAINT_BLACK(t); \
        TPAINT_RED(tt); \
        prefix##rotate_## left(tm, tt); \
        break;  \
      } \
    } \
  } \
}\
static inline void prefix##delete_fixup(struct tname *tm, struct TNN(tname)* t) {\
  /* n - nút, s - nút cạnh n (side), cn - nút dưới phía gần n (close node),
   * dn - nút dưới phía xa n (distant node) */\
  struct TNN(tname) *n = NULL, *s, *cn, *dn; \
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
      if (TIS_RED(s)) { \
        /* Trường hợp 1, s là nút đỏ (vì vậy T, CN, DN là các nút đen)
         * => Xoay trái ở t, tô t thành đỏ và S thành đen.
         *
         *     T               S
         *    / \             / \
         *   N   s    -->    t   DN
         *      / \         / \
         *     CN  DN      N   CN <- s mới
         */ \
        prefix##rotate_## left(tm, t); \
        TPAINT_RED(t); \
        TPAINT_BLACK(s); \
        s = t->right; \
      } \
      dn = s->right; \
      if (TIS_BLACK(dn)) { \
        cn = s->left; \
        if (TIS_BLACK(cn)) { \
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
          TPAINT_RED(s); \
          if (TIS_RED(t)) { \
            TPAINT_BLACK(t); \
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
        prefix##rotate_## right(tm, s); \
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
        prefix##rotate_ ##left(tm, t); \
        TPAINT(cn, t->color); \
        TPAINT_BLACK(t); \
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
      prefix##rotate_ ##left(tm, t); \
      TPAINT(s, t->color); \
      TPAINT_BLACK(t); \
      TPAINT_BLACK(dn); \
      break; \
    } else { \
      /* Đối xứng với trường hợp n là con trái của t */ \
      s = t->left; \
      if (TIS_RED(s)) { \
        prefix##rotate_## right(tm, t); \
        TPAINT_RED(t); \
        TPAINT_BLACK(s); \
        s = t->left; \
      } \
      dn = s->left; \
      if (TIS_BLACK(dn)) { \
        cn = s->right; \
        if (TIS_BLACK(cn)) { \
          TPAINT_RED(s); \
          if (TIS_RED(t)) { \
            TPAINT_BLACK(t); \
          } else { \
            n = t; \
            t = n->top; \
            if (t) { \
              continue; \
            } \
          } \
          break; \
        } \
        prefix##rotate_## left(tm, s); \
        s = t->left; \
      } \
      dn = s->left; \
      prefix##rotate_ ##right(tm, t); \
      TPAINT(s, t->color); \
      TPAINT_BLACK(t); \
      TPAINT_BLACK(dn); \
      break; \
    } \
  } \
}\
struct TNN(tname) *TNN(tname)(ktype key, vtype value) { \
  struct TNN(tname) *nn = malloc(sizeof(struct TNN(tname))); \
  nn->key = key; \
  nn->value = value; \
  TPAINT_RED(nn); \
  nn->left = nn->right = nn->top = NULL; \
  return nn; \
} \
struct TNN(tname) *prefix##left_most(struct TNN(tname) *n) { \
  while (n->left) { \
    n = n->left; \
  } \
  return n; \
} \
struct TNN(tname) *prefix##right_most(struct TNN(tname) *n) { \
  while (n->right) { \
    n = n->right; \
  } \
  return n; \
} \
struct TNN(tname) *prefix##left_deepest(struct TNN(tname) *n) { \
  for (;;) { \
    if (n->left) { \
      n = n->left; \
    } else if (n->right) { \
      n = n->right; \
    } else { \
      break; \
    } \
  } \
  return n; \
} \
struct TNN(tname) *prefix##next_lrn(struct TNN(tname) *n) { \
  struct TNN(tname) *top = n->top; \
  if (top && n == top->left && top->right) { \
    return prefix##left_deepest(top->right); \
  } \
  return top; \
} \
struct TNN(tname) *prefix##next_lnr(struct TNN(tname) *n) { \
  if (n->right) { \
    return prefix##left_most(n->right); \
  } \
  struct TNN(tname) *top = n->top; \
  while (top != NULL && n == top->right) { \
    n = top; \
    top = n->top; \
  } \
  return top; \
} \
struct TNN(tname) *prefix##prev_lnr(struct TNN(tname) *n) { \
  if (n->left) { \
    return prefix##right_most(n->left); \
  } \
  struct TNN(tname) *top = n->top; \
  while (top != NULL && n == top->left) { \
    n = top; \
    top = n->top; \
  } \
  return top; \
} \
struct TNN(tname) *prefix##first_lrn(struct tname *tm) { \
  return tm->root? prefix##left_deepest(tm->root): NULL; \
} \
struct TNN(tname) *prefix##first_lnr(struct tname *tm) { \
  return tm->root? prefix##left_most(tm->root): NULL; \
} \
struct TNN(tname) *prefix##last_lnr(struct tname *tm) { \
  return tm->root? prefix##right_most(tm->root): NULL; \
} \
struct TNN(tname) *prefix##pval_node(void *pv) { \
  return pv? pv - offsetof(struct TNN(tname), value): NULL; \
} \
struct tname *prefix##create(compare_fnt cmp) { \
  if (!cmp) { \
    FLOG("Không thể tạo bảng cây nếu không biết hàm so sánh."); \
    return NULL; \
  } \
  struct tname *tm = malloc(sizeof(struct tname)); \
  if (!tm) { \
    FLOG("Không thể cấp phát bộ nhớ."); \
    return NULL; \
  } \
  tm->root = NULL; \
  tm->cmp = cmp; \
  tm->fk = NULL; \
  tm->fv = NULL; \
  tm->size = 0; \
  return tm; \
} \
struct tname *tname(compare_fnt cmp) { \
  return prefix##create(cmp); \
} \
void prefix##clear(struct tname *tm) { \
  struct TNN(tname) *n = prefix##first_lrn(tm); \
  struct TNN(tname) *tmp = NULL; \
  while (n) { \
    if (tm->fk) { \
      tm->fk(n->key); \
    } \
    if (tm->fv) { \
      tm->fv(n->value); \
    } \
    tmp = n; \
    n = prefix##next_lrn(n); \
    free(tmp); \
  } \
  tm->size = 0; \
} \
void prefix##free(struct tname *tm) { \
  prefix##clear(tm); \
  free(tm); \
} \
static struct tname *prefix##delete(struct tname *tm, struct TNN(tname) *dn) { \
  struct TNN(tname) *node = dn; \
  struct TNN(tname) *child = node->right, \
            *tmp = node->left, \
            *top, *rebalance; \
  /* Trường hợp 1: Nếu nút đang xóa có không quá 1 nút con (dễ)
   *
   * Nếu chỉ có 1 con thì nút con phải là nút đỏ do tính chất 5,
   * và nó phải là nút đen theo tính chất 4. Có thể điều chỉnh
   * mầu trong lân cận để giữ các tính chất cây đỏ-dên.
   */ \
  if (!tmp) { \
    prefix##change(tm, node, child); \
    if (child) { \
      /* node phải là nút đen và child phải là nút đỏ */ \
      TPAINT_BLACK(child); \
      rebalance = NULL; \
    } else { \
      /* Cả 2 con của node đều là NULL => Vị trí cũ của node
       * được thay bằng con trỏ NULL. Nếu node là nút đen thì
       * độ cao đen của đường đi qua node giảm 1 => vi phạm tính chất 5. */ \
      rebalance = TIS_BLACK(node)? node->top: NULL; \
    } \
  } else if (!child) { \
    /* node phải là nút đen và tmp là nút đỏ */ \
    prefix##change(tm, node, tmp); \
    TPAINT_BLACK(tmp); \
    rebalance = NULL; \
  } else { \
    struct TNN(tname) *sss = child, *child2; \
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
      TPAINT_BLACK(child2); \
      rebalance = NULL; \
    } else {\
      /* child2 == NULL => Vị trí cũ của sss được thay bằng NULL,
       * Nếu sss là nút đen thì độ cao đen của đường đi qua child2
       * bị giảm 1 => vi phạm tính chất 5 */ \
      rebalance = TIS_BLACK(sss) ? top: NULL; \
    }\
    prefix##change(tm, node, sss); \
    TPAINT(sss, node->color); \
  } \
  if (rebalance) { \
    /* Nút rebalance có 1 con NULL sao cho đường đi qua đó
     * ngắn hơn 1 so với các đường đi khác */ \
    prefix##delete_fixup(tm, rebalance); \
  } \
  free(dn); \
  --(tm->size); \
  return tm; \
} \
vtype *prefix##put(struct tname *tm, ktype key, vtype value) { \
  struct TNN(tname) *nn = TNN(tname)(key, value), \
                    *top = NULL, \
                    *x = tm->root, \
                   **loc = &tm->root; \
  int rl = 0; \
  while (x) { \
    rl = tm->cmp(&key, &x->key); \
    if (rl == 0) { \
      free(nn); \
      return &x->value; \
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
  *loc = nn; \
  nn->top = top; \
  if (top == NULL) { \
    nn->color = BLACK; \
  } else if (TIS_RED(top)) { \
    /* Vi phạm tính chất 4 (sau thao tác thêm vào chỉ có tính chất 4
       có thể bị vi phạm). */ \
    prefix##put_fixup(tm, nn); \
  } \
  ++tm->size; \
  return NULL; \
} \
vtype *prefix##get(struct tname *tm, ktype key) { \
  struct TNN(tname) *x = tm->root; \
  while (x) { \
    int rl = tm->cmp(&key, &x->key); \
    if (rl == 0) { \
      break; \
    } \
    x = rl < 0? x->left: x->right; \
  } \
  if (!x) { \
    return NULL; \
  } \
  return &x->value; \
} \
struct tname *prefix##remove(struct tname *tm, ktype key) { \
  struct TNN(tname) *n = prefix##pval_node(prefix##get(tm, key)); \
  if (!n) { \
    return NULL; \
  } \
  if (tm->fk) { \
    tm->fk(n->key); \
  } \
  if (tm->fv) { \
    tm->fv(n->value); \
  }\
  prefix##delete(tm, n);\
  return tm; \
}

#define TDECL_IMPL(tname, keytype, valtype, prefix) \
TDECL(tname, keytype, valtype, prefix); \
TIMPL(tname, keytype, valtype, prefix)

#endif  // CONT_TMAP_H_

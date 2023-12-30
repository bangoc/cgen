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
#define TSET_PC(n, p, c) (n)->top = (p); TPAINT(n, c)

#define TDECL(tname, ktype, vtype, prefix) \
TDEFN(tname, ktype, vtype); \
struct TNN(tname) *prefix##left_most(struct TNN(tname) *n); \
struct TNN(tname) *prefix##right_most(struct TNN(tname) *n); \
struct TNN(tname) *prefix##left_deepest(struct TNN(tname) *n); \
struct TNN(tname) *prefix##next_lrn(struct TNN(tname) *n); \
struct TNN(tname) *prefix##next_lnr(struct TNN(tname) *n); \
struct TNN(tname) *prefix##prev_lnr(struct TNN(tname) *n); \
struct TNN(tname) *prefix##first_lrn(struct tname *t); \
struct TNN(tname) *prefix##first_lnr(struct tname *t); \
struct TNN(tname) *prefix##last_lnr(struct tname *t); \
struct TNN(tname) *prefix##pval_node(void *pv); \
struct tname *prefix##create(compare_fnt cmp); \
struct tname *tname(compare_fnt cmp); \
void prefix##clear(struct tname *t); \
void prefix##free(struct tname *t); \
vtype *prefix##put(struct tname *t, ktype key, vtype value); \
vtype *prefix##get(struct tname *t, ktype key); \
struct tname *prefix##remove(struct tname *t, ktype key)

#define TIMPL(tname, ktype, vtype, prefix) \
static inline void prefix##change(struct TNN(tname) *old_node, \
        struct TNN(tname) *new_node, struct tname *t) { \
  struct TNN(tname) *top = old_node->top; \
  if (top) { \
    if (top->left == old_node) { \
      top->left = new_node; \
    } else { \
      top->right = new_node; \
    } \
  } else { \
    t->root = new_node; \
  } \
  if (new_node) { \
    (new_node)->top = top; \
  } \
} \
/*     p                            p
         x                            r
      l     r <- y                   x
          rl                       l   rl
*/ \
static inline void prefix##rotate_left(struct tname *t, struct TNN(tname) *x) { \
  struct TNN(tname) *y = x->right; \
  x->right = y->left; \
  if (y->left != NULL) { \
    y->left->top = x; \
  } \
  prefix##change(x, y, t); \
  y->left = x; \
  x->top = y; \
}\
/*     p                       p
         x                        l
   y->l     r                       x
        lr                        lr  r
*/ \
static inline void prefix##rotate_right(struct tname *t, struct TNN(tname) *x) { \
  struct TNN(tname) *y = x->left; \
  x->left = y->right; \
  if (y->right != NULL) { \
    y->right->top = x; \
  } \
  prefix##change(x, y, t); \
  y->right = x; \
  x->top = y; \
}\
static inline void prefix##put_fixup(struct tname *t, struct TNN(tname) *n) {\
  /*
   * Các biến:
   * t - con trỏ tới cây (tree)
   * n - ban đầu là nút mới được thêm vào (node)
   * p - là đỉnh của n (n->top)
   * u - nút đối xứng của p trong cây, chú bác của n (uncle)
   * pp - là đỉnh của p (p->top)
   *
   * Trong các sơ đồ minh họa cây thì nút có tên được viết hoa là nút đen,
   *    nút có tên viết thường là nút đỏ, nút có thể là đen hoặc đỏ
   *    (không ảnh hưởng đển tính đúng đắn) thì được đặt trong dấu ()
   */ \
  struct TNN(tname) *p = n->top, *pp = p->top; \
  /* Các bất biến của vòng lặp:
   *  + p là đỉnh của n, tính chất cây đỏ đen chỉ bị vi phạm ở đoạn
   *    p-n: n và p là các nút đỏ (tính chất 4). Vấn đề này được
   *    khắc phục trong quá trình n được đẩy lên phía gốc.
   * Ban đầu n là nút mới được thêm vào, sau mỗi vòng lặp n tiến
   * gần hơn về phía gốc của cây. Vòng lặp dừng lại khi p ==
   * NULL (n là gốc của cây) hoặc p được tô mầu đen.
   *
   * Trong vòng lặp chúng ta có
   *  + n->top != NULL và p->top != NULL (bởi vì n và p
   * là các nút đỏ)
   */ \
  while (1) { \
    if (p == pp->left) { \
      if (TIS_RED(pp->right)) { \
        /*     PP                pp  <- n mới
             p   u  thành>>>   P    U
          ->n <-                n mới có thể vi phạm tính chất 4 nếu pp->top là đỏ,
                                có thể là con trái hoặc con phải trong cây.
         */ \
        TPAINT_BLACK(p); \
        TPAINT_BLACK(pp->right); \
        TPAINT_RED(pp); \
        n = pp; \
        p = n->top; \
        if (p == NULL) { \
          /* n là gốc của cây */ \
          TPAINT_BLACK(n); \
          break; \
        } \
        pp = p->top; \
        if (TIS_BLACK(p)) { \
          /* Các tính chất đã được thỏa mãn */ \
          break; \
        } \
      } else { \
        if (n == p->right) { \
          /*     PP                  PP
               p    U  thành>>>   n <-p  U
                n               p  <-n mới
           */ \
          prefix##rotate_## left(t, p); \
          n = p; \
          p = n->top; \
        } \
        /*
         + n là con trái của p
                PP                   pp
             p     U  lật mầu >>   P   U
           n                      n
          >>> & sau khi xoay phải ở PP thành =>>>
              P
            n    pp
                    U
            Thỏa mãn các tính chất của cây đỏ đen
         */ \
        TPAINT_BLACK(p); \
        TPAINT_RED(pp); \
        prefix##rotate_## right(t, pp); \
        break;  \
      } \
    } else { \
      /* Trường hợp p là con phải của pp */ \
      if (TIS_RED(pp->left)) { \
        /*     PP                pp  <- n mới
             u   p  thành>>>   U    P
              ->n <-            n mới có thể vi phạm tính chất 4 nếu pp->top là đỏ,
                                có thể là con trái hoặc con phải trong cây.
         */ \
        TPAINT_BLACK(p); \
        TPAINT_BLACK(pp->left); \
        TPAINT_RED(pp); \
        n = pp; \
        p = n->top; \
        if (p == NULL) { \
          /* n là gốc của cây */ \
          TPAINT_BLACK(n); \
          break; \
        } \
        pp = p->top; \
        if (TIS_BLACK(p)) { \
          /* Các tính chất đã được thỏa mãn */ \
          break; \
        } \
      } else { \
        if (n == p->left) { \
          /*     PP                    PP
               U    p    thành>>>    U    n <-p
                  n                          p  <-n mới
           */ \
          prefix##rotate_## right(t, p); \
          n = p; \
          p = n->top; \
          pp = p->top; \
        } \
        /*
         + n là con phải của p
                PP                      pp
              U    p     lật mầu >>   U    P
                     n                       n
          >>> & sau khi xoay trái ở pp thành =>>>
                    P
                 pp    n
               U
            Thỏa mãn các tính chất của cây đỏ đen
         */ \
        TPAINT_BLACK(p); \
        TPAINT_RED(pp); \
        prefix##rotate_## left(t, pp); \
        break;  \
      } \
    } \
  } \
}\
static inline void prefix##delete_fixup(struct tname *t, struct TNN(tname)* p) {\
  /*n - node, s - sibling, cn - close nephew, dn - distant nephew */\
  struct TNN(tname) *n = NULL, *s, *dn, *cn; \
  /*
   * Các tính chất bất biến trong vòng lặp:
   * - n là nút đen (== NULL trong lần lặp đầu tiên)
   * - n không phải là nút gốc (top của nó khác NULL)
   * - Tất cả các đường dẫn tới lá đi qua p va n có số
   *   lượng nút đen ít hơn 1 so với các đường dẫn khác.
   */ \
  /* Trong các sơ đồ cây nút viết hoa là nút đen,
   * nút viết thường là nút đỏ, nút trong ngoặc có thể là đỏ hoặc đen.
   */ \
  /* Trường hợp 1.1 - Xoay trái ở p
   *
   *     P               S
   *    / \             / \
   *   N   s    -->    p   DN
   *      / \         / \
   *     CN  DN      N   CN <- s mới
   */ \
  /*
   * Trường hợp 1.2 - Đảo mầu s, p có thể có mầu bất kỳ (có mầu đỏ
   * sau khi xử lý trường hợp 1)
   *
   *    (p)           (p)
   *    / \           / \
   *   N   S    -->  N   s
   *      / \           / \
   *     CN  DN        CN  DN
   *
   * Vi phạm ràng buộc 5 có thể được khắc phục bằng cách đảo mầu p
   * thành đen nếu nó là nút đỏ, hoặc đệ quy tại p nếu ngược lại.
   */ \
  /*
   * Trường hợp 1.3 - Xoay phải tại s (p có thể có mầu bất kỳ)
   *
   *              (p)           (p)
   *              / \           / \
   *             N   S    -->  N   cn
   *                / \             \
   *               cn  DN            S
   *                                  \
   *                                   DN
   * Lưu ý: + p có thể là nút đỏ, và nếu như vậy thì cả p và
   * cn đều là các nút đỏ sau khi xoay (vi phạm ràng buộc 4).
   *
   * + Đường đi từ p qua cn sau đó rẽ về phía N bị giảm 1
   * nút đen (S, vi phạm tính chất 5).
   *
   * Các vấn đề  này được xử lý trong trường hợp 4: Sau khi
   * xoay phải tại p, cn được tô bằng mầu của p, dn và p
   * được tô mầu đen)
   *
   *   (p)            (cn)
   *   / \            /  \
   *  N   cn   -->   P    S
   *       \        /      \
   *        S      N        DN
   *         \
   *          DN
   */ \
  /* Trường hợp 1.4 - Xoay trái ở p + đảo mầu các nút,
   * p và cn có thể có mầu bất kỳ trước khi xoay. Sau khi xoay
   * mầu của cn không thay đổi, s có mầu cũ của p, p và dn được tô mầu đen.
   *
   *      (p)             (s)
   *      / \             / \
   *     N   S     -->   P   Dn
   *        / \         / \
   *      (cn) dn      N  (cn)
   */ \
  /*
   * Trường hợp 2.1 - Xoay phải ở p
   *
   *      P                  S
   *     / \                / \
   *    s   N -->         CN   p
   *   / \                    / \
   *  CN  DN        s mới -> DN   N
   */ \
  /*
   * Trường hợp 2.2 - Đảo mầu s, p có thể có mầu bất kỳ (mầu đỏ sau
   * khi xử lý trường hợp 1)
   *
   *        (p)           (p)
   *        / \           / \
   *       S   N -->     s   N
   *      / \           / \
   *     CN  DN        CN  DN
   *
   * Vi phạm ràng buộc 5, có thể được khắc phục bằng cách đảo mầu p
   * thành đen nếu nó là nút đỏ, hoặc đệ quy tại p nếu ngược lại.
   */ \
  /*
   * Trường hợp 2.3 - Xoay phải tại s (p có thể có mầu bất
   * kỳ)
   *
   *             (p)            (p)
   *             / \            / \
   *            S  N  -->     cn   N
   *           / \             \
   *          cn  DN            S
   *                             \
   *                              DN
   * Nếu p là nút đỏ, thì cả p và CN đều là các nút đỏ sau khi xoay
   *   => Vi phạm ràng buộc 4.
   *
   * + Đường đi từ p qua cn sau đó rẽ về phía N bị giảm một
   * nút đen (S, vi phạm tính chất 5).
   *
   * Các vấn đề  này được xử lý trong trường hợp 4: Sau khi
   * xoay trái tại top, cn được tô bằng mầu của p, dn và p
   * được tô mầu đen)
   *
   *   (p)            (cn)
   *   / \            /  \
   *  N   cn   -->   P    S
   *       \        /      \
   *        S      N        DN
   *         \
   *          DN
   */ \
  /* Trường hợp 2.4 - Xoay phải ở p + đảo mầu các nút,
   * p và cn có thể có mầu bất kỳ trước khi xoay. Sau khi xoay
   * mầu của cn không thay đổi, s có mầu cũ của p, p và dn được tô mầu đen.
   *
   *          (p)             (s)
   *          / \             /  \
   *         S   N   -->    DN    P
   *        / \                 /   \
   *       dn (cn)            (cn)   N
   */ \
  while (1) { \
    s = p->right; \
    if (n != s) { \
      if (TIS_RED(s)) { \
        /* Trường hợp 1.1 */ \
        prefix##rotate_## left(t, p); \
        TPAINT_RED(p); \
        TPAINT_BLACK(s); \
        s = p->right; \
      } \
      dn = s->right; \
      if (TIS_BLACK(dn)) { \
        cn = s->left; \
        if (TIS_BLACK(cn)) { \
          /* Trường hợp 1.2 */ \
          TPAINT_RED(s); \
          if (TIS_RED(p)) { \
            TPAINT_BLACK(p); \
          } else { \
            n = p; \
            p = n->top; \
            if (p) { \
              continue; \
            } \
          } \
          break; \
        } \
        /* Trường hợp 1.3 */ \
        prefix##rotate_## right(t, s); \
        s = p->right; \
      } \
      /* Trường hợp 1.4 */ \
      dn = s->right; \
      prefix##rotate_ ##left(t, p); \
      TPAINT(s, p->color); \
      TPAINT_BLACK(p); \
      TPAINT_BLACK(dn); \
      break; \
    } else { \
      s = p->left; \
      if (TIS_RED(s)) { \
        /* Trường hợp 2.1 */ \
        prefix##rotate_## right(t, p); \
        TPAINT_RED(p); \
        TPAINT_BLACK(s); \
        s = p->left; \
      } \
      dn = s->left; \
      if (TIS_BLACK(dn)) { \
        cn = s->right; \
        if (TIS_BLACK(cn)) { \
          /* Trường hợp 2.2 */ \
          TPAINT_RED(s); \
          if (TIS_RED(p)) { \
            TPAINT_BLACK(p); \
          } else { \
            n = p; \
            p = n->top; \
            if (p) { \
              continue; \
            } \
          } \
          break; \
        } \
        /* Trường hợp 2.3 */ \
        prefix##rotate_## left(t, s); \
        s = p->left; \
      } \
      /* Trường hợp 2.4 */ \
      dn = s->left; \
      prefix##rotate_ ##right(t, p); \
      TPAINT(s, p->color); \
      TPAINT_BLACK(p); \
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
struct TNN(tname) *prefix##first_lrn(struct tname *t) { \
  return prefix##left_deepest(t->root); \
} \
struct TNN(tname) *prefix##first_lnr(struct tname *t) { \
  return prefix##left_most(t->root); \
} \
struct TNN(tname) *prefix##last_lnr(struct tname *t) { \
  return prefix##right_most(t->root); \
} \
struct TNN(tname) *prefix##pval_node(void *pv) { \
  return pv? pv - offsetof(struct TNN(tname), value): NULL; \
} \
struct tname *prefix##create(compare_fnt cmp) { \
  if (!cmp) { \
    FLOG("Không thể tạo bảng cây nếu không biết hàm so sánh."); \
    return NULL; \
  } \
  struct tname *t = malloc(sizeof(struct tname)); \
  if (!t) { \
    FLOG("Không thể cấp phát bộ nhớ."); \
    return NULL; \
  } \
  t->root = NULL; \
  t->cmp = cmp; \
  t->fk = NULL; \
  t->fv = NULL; \
  t->size = 0; \
  return t; \
} \
struct tname *tname(compare_fnt cmp) { \
  return prefix##create(cmp); \
} \
void prefix##clear(struct tname *t) { \
  struct TNN(tname) *n = prefix##first_lrn(t); \
  struct TNN(tname) *tmp = NULL; \
  while (n) { \
    if (t->fk) { \
      t->fk(n->key); \
    } \
    if (t->fv) { \
      t->fv(n->value); \
    } \
    tmp = n; \
    n = prefix##next_lrn(n); \
    free(tmp); \
  } \
  t->size = 0; \
} \
void prefix##free(struct tname *t) { \
  prefix##clear(t); \
  free(t); \
} \
static struct tname *prefix##delete(struct tname *t, struct TNN(tname) *dn) { \
  struct TNN(tname) *node = dn; \
  struct TNN(tname) *child = node->right, \
            *tmp = node->left, \
            *top, *rebalance; \
  enum tcolors c; \
  /* Trường hợp 1: Nếu nút đang xóa có không quá 1 nút con (dễ)
     *
     * Nếu chỉ có 1 con thì nút con phải là nút đỏ do tính chất 5,
     * và nó phải là nút đen theo tính chất 4. Chúng ta điều chỉnh
     * mầu trong lân cận để tránh gọi hàm sửa mầu sau này.
     */ \
  if (!tmp) { \
    top = node->top; \
    c = node->color; \
    prefix##change(node, child, t); \
    if (child) { \
      TPAINT(child, c); \
      rebalance = NULL; \
    } else { \
      rebalance = c == BLACK? top: NULL; \
    } \
  } else if (!child) { \
    top = node->top; \
    c = node->color; \
    prefix##change(node, tmp, t); \
    TPAINT(tmp, c); \
    rebalance = NULL; \
  } else { \
    struct TNN(tname) *successor = child, *child2; \
    tmp = child->left; \
    if (!tmp) { \
      /* Trường hợp 2: Nút liền sau node là con phải của node.
       *
       *    (n)          (s)
       *    / \          / \
       *  (x) (s)  ->  (x) (c)
       *        \
       *        (c)
       */ \
      top = successor; \
      child2 = successor->right; \
    } else { \
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
       */ \
      do { \
        top = successor; \
        successor = tmp; \
        tmp = tmp->left; \
      } while (tmp); \
      child2 = successor->right; \
      top->left = child2; \
      successor->right = child; \
      child->top = successor; \
    } \
    tmp = node->left; \
    successor->left = tmp; \
    tmp->top = successor; \
    if (child2) { \
      TSET_PC(child2, top, BLACK); \
      rebalance = NULL; \
    } else { \
      enum tcolors c2 = successor->color; \
      rebalance = c2 == BLACK? top: NULL; \
    } \
    tmp = node->top; \
    c = node->color; \
    prefix##change(node, successor, t); \
    TPAINT(successor, c); \
  } \
  if (rebalance) { \
    prefix##delete_fixup(t, rebalance); \
  } \
  free(dn); \
  return t; \
} \
vtype *prefix##put(struct tname *t, ktype key, vtype value) { \
  struct TNN(tname) *nn = TNN(tname)(key, value), \
                    *top = NULL, \
                    *x = t->root, \
                   **loc = &t->root; \
  int rl = 0; \
  while (x) { \
    rl = t->cmp(&key, &x->key); \
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
    prefix##put_fixup(t, nn); \
  } \
  ++t->size; \
  return NULL; \
} \
vtype *prefix##get(struct tname *t, ktype key) { \
  struct TNN(tname) *x = t->root; \
  while (x) { \
    int rl = t->cmp(&key, &x->key); \
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
struct tname *prefix##remove(struct tname *t, ktype key) { \
  struct TNN(tname) *n = prefix##pval_node(prefix##get(t, key)); \
  if (!n) { \
    return NULL; \
  } \
  if (t->fk) { \
    t->fk(n->key); \
  } \
  if (t->fv) { \
    t->fv(n->value); \
  }\
  prefix##delete(t, n);\
  --(t->size); \
  return t; \
}

#define TDECL_IMPL(tname, keytype, valtype, prefix) \
TDECL(tname, keytype, valtype, prefix); \
TIMPL(tname, keytype, valtype, prefix)

#endif  // CONT_TMAP_H_

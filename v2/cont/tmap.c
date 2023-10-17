/* (C) Nguyễn Bá Ngọc 2023 */
/**
 * @file 
 * @brief Triển khai cấu trúc tra cứu dựa trên
 * cây đỏ đen với khóa và giá trị có kiểu \ref gtype.
 */

#include "cont/tmap.h"

#include <stdlib.h>

/** Các giá trị mầu của nút.
 *  đỏ = 0, đen = 1 như vậy chúng ta có 
 * tổng giá trị mầu = số lượng nút đen
 */
enum tcolors {
  RED = 0,
  BLACK = 1
};

/**
 * Cấu trúc nút của tmap, là mở rộng nút của cây đỏ đen.
 * tnode = Red-black tree map node
 *
 * \private Người sử dụng không cần thao tác với kiểu này.
 */
struct tnode {
  /** 
   * Khóa, bắt buộc là phần tử đầu tiên để có thể
   * ép kiểu thành con trỏ tới nút và ngược lại.
   */
  gtype key;

  /** Giá trị */
  gtype value;
  
  /** Mầu của nút */
  enum tcolors color;

  /** Con trỏ tới nút con trái */
  struct tnode *left;

  /** Nút con phải */
  struct tnode *right;

  /** Nút đỉnh */
  struct tnode *top;
};

#define TCOLOR_OF(n) ((n)? (n)->color: BLACK)
#define TIS_RED(n) (TCOLOR_OF(n) == RED)
#define TIS_BLACK(n) (TCOLOR_OF(n) == BLACK)
#define TPAINT_BLACK(n) ((n)->color = BLACK)
#define TPAINT_RED(n) ((n)->color = RED)
#define TPAINT(n, c) ((n)->color = (c))
#define TSET_PC(n, p, c) (n)->top = (p); TPAINT(n, c)

struct tnode *tnode(const gtype key, const gtype value) {
  struct tnode *nn = malloc(sizeof(struct tnode));
  if (!nn) {
#ifdef CGEN_DEBUG
    FLOG("Không thể cấp phát bộ nhớ cho nút.");
#endif  // CGEN_DEBUG
    return NULL;
  }
  nn->key = key;
  nn->value = value;
  TPAINT_RED(nn);
  nn->left = nn->right = nn->top = NULL;
  return nn;
}

/**
 * Cấu trúc điều khiển của bảng cây tmap, được tạo bằng hàm
 * tmap = red black map tree
 *
 * rbm_create(gtype_cmp_t cmp, gtype_free_t free_key, gtype_free_t free_value).
 *
 * Các macro hỗ trợ:
 * 
 *   #TMTRAVERSE(k, v, map) - Duyệt tuần tự các cặp trong map.
 */
struct tmap {
  struct tnode *root;
  gtype_cmp_t cmp;
  gtype_free_t fk, fv;
  long size;
};

struct tmap *tcreate(gtype_cmp_t cmp) {
  if (!cmp) {
#ifdef CGEN_DEBUG
    FLOG("Không thể tạo bảng cây nếu không biết hàm so sánh.");
    return NULL;
#endif  // CGEN_DEBUG    
  }
  struct tmap *t = malloc(sizeof(struct tmap));
  if (!t) {
#ifdef CGEN_DEBUG
    FLOG("Không thể cấp phát bộ nhớ.");
    return NULL;
#endif  // CGEN_DEBUG
  }
  t->root = NULL;
  t->cmp = cmp;
  t->fv = t->fk = NULL;
  t->size = 0;
  return t;
}

#define TCHANGE(old_node, new_node, parent, t) \
  do { \
    if (parent) { \
      if (parent->left == old_node) { \
        parent->left = new_node; \
      } else { \
        parent->right = new_node; \
      } \
    } else { \
      t->root = new_node; \
    } \
  } while (0)

/* Xoay từ trái sang phải hoặc xoay từ phải sang trái */
/* x là trục xoay */
#define TROTATE(t, x, right, left) \
  do { \
    struct tnode *_y = (x)->right; \
    (x)->right = _y->left; \
    if (_y->left != NULL) { \
      _y->left->top = (x); \
    } \
    _y->top = (x)->top; \
    TCHANGE(x, _y, (x)->top, t); \
    _y->left = (x); \
    (x)->top = _y; \
  } while (0)

static void tinsert_fixup(struct tmap *t, struct tnode *n, struct tnode *p) {
  /*
   * Các biến:
   * t - con trỏ tới cây (tree)
   * n - ban đầu là nút mới được thêm vào (node)
   * p - là đỉnh của n (parent, n->top)
   * u - nút đối xứng của p trong cây, chú bác của n (uncle)
   * gp - ông của n, là đỉnh của p (grandparent, p->top)
   *
   * Trong các ví dụ minh họa thì nút có tên được viết hoa là nút đen,
   *    nút có tên viết thường là nút đỏ, nút có thể là đen hoặc đỏ
   *    (không ảnh hưởng đển tính đúng đắn) thì được đặt trong dấu ()
   */
  while (1) {
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
     */

    if (p == p->top->left) {
#define IMPL_INSERT_FIXUP(left, right) \
      struct tnode *_u = p->top->right; \
      if (TIS_RED(_u)) { \
        /*     GP                gp  <- n mới                      \
             p   u  thành>>>   P    U                              \
          ->n <-     có thể vi phạm tính chất 4 nếu gp->top là đỏ,\
                     n có thể là con trái hoặc con phải của p     \
         */ \
        TPAINT_BLACK(p); \
        TPAINT_BLACK(_u); \
        TPAINT_RED(p->top); \
        n = p->top; \
        p = n->top; \
        if (p == NULL) { \
          /* n là gốc của cây */ \
          TPAINT_BLACK(n); \
          break; \
        } \
        if (TIS_BLACK(p)) { \
          /* Các tính chất đã được thỏa mãn */ \
          break; \
        } \
      } else { \
        if (n == n->top->right) { \
          /*     GP                  GP           \
               p    U  thành>>>   n <-p  U        \
                n               p  <-n mới        \
           */ \
          TROTATE(t, p, right, left); \
          n = p; \
          p = n->top; \
        } \
        /*   \
         + n là con trái của p                        \
                GP                   gp               \
             p     U  lật mầu >>   P   U              \
           n                      n                   \
          >>> & sau khi xoay phải ở GP thành =>>>     \
              P                                       \
            n    gp                                   \
                    U                                 \
            Thỏa mãn các tính chất của cây đỏ đen     \
         */                                           \
        TPAINT_BLACK(p); \
        TPAINT_RED(p->top); \
        p = p->top; \
        TROTATE(t, p, left, right); \
        break;  \
      }
      IMPL_INSERT_FIXUP(left, right)
    } else {
      IMPL_INSERT_FIXUP(right, left)
    }
#undef IMPL_INSERT_FIXUP
  }
}

gtype *tinsert(struct tmap *t, const gtype key, const gtype value) {
  struct tnode *nn = tnode(key, value);
  if (!nn) {
#ifdef CGEN_DEBUG
    FLOG("Không thể tạo nút mới.");
    return NULL;
#endif  // CGEN_DEBUG    
  }
  struct tnode *top = NULL;
  struct tnode *x = t->root;
  struct tnode **loc = &t->root;
  int rl = 0;
  while (x) {
    rl = t->cmp(&key, &x->key);
    if (rl == 0) {
      free(nn);
      return &x->value;
    } 
    top = x;
    if (rl < 0) {
      x = top->left;
      loc = &top->left;
    } else {
      x = top->right;
      loc = &top->right;
    }
  }
  *loc = nn;
  nn->top = top;
  if (top == NULL) {
    nn->color = BLACK;
  } else if (TIS_RED(top)) {
    /* Vi phạm tính chất 4 (sau thao tác thêm vào chỉ có tính chất 4
       có thể bị vi phạm). */
    tinsert_fixup(t, nn, top);
  }
  ++t->size;
  return NULL;
}

struct tnode *tsearch(struct tmap *t, gtype *key) {
  if (!t || !t->cmp) {
#ifdef CGEN_DEBUG
    FLOG("Bảng ở trạng thái không hợp lệ.");
#endif  // CGEN_DEBUG
    return NULL;    
  }
  int rl;
  struct tnode *x = t->root;
  while (x) {
    rl = t->cmp(key, (gtype*)x);
    if (rl == 0) {
      return x;
    }
    x = rl < 0? x->left: x->right;
  }
  return NULL;
}

static void tdelete_fixup(struct tmap *t, struct tnode *parent) {
  struct tnode *node = NULL, *sibling,
          *cn,  // Con của sibling ở phía gần node (close nephew)
          *dn;  // Con của sibling ở phía xa node (distant nephew)
  while (1) {
    /*
    * Các tính chất bất biến trong vòng lặp:
    * - node là nút đen (hoặc NULL trong lần lặp đầu tiên)
    * - node không phải là nút gốc (top của nó khác NULL)
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
      if (TIS_RED(sibling)) { \
        /* \
         * Trường hợp 1 - Xoay trái ở parent      \
         *                                        \
         *     P               S                  \
         *    / \             / \                 \
         *   N   s    -->    p   Dn               \
         *      / \         / \                   \
         *     Cn  Dn      N   Cn <- sibling mới  \
         */                                       \
        TROTATE(t, parent, right, left); \
        TPAINT_RED(parent); \
        TPAINT_BLACK(sibling); \
        sibling = parent->right; \
      } \
      dn = sibling->right; \
      if (TIS_BLACK(dn)) { \
        cn = sibling->left; \
        if (TIS_BLACK(cn)) { \
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
          TPAINT_RED(sibling); \
          if (TIS_RED(parent)) { \
            TPAINT_BLACK(parent); \
          } else { \
            node = parent; \
            parent = node->top; \
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
         * Lưu ý: + p có thể là nút đỏ, và nếu như vậy thì cả p và   \
         * Cn đều là các nút đỏ sau khi xoay (vi phạm ràng buộc 4).  \
         *                                                           \
         * + Đường đi từ p qua cn sau đó rẽ về phía N bị giảm một    \
         * nút đen (S, vi phạm tính chất 5).                         \
         *                                                           \
         * Các vấn đề  này được xử lý trong trường hợp 4: Sau khi    \
         * xoay trái tại parent, cn được tô bằng mầu của p, dn và p  \
         * được tô mầu đen)                                          \
         *                                                           \
         *   (p)            (cn)                                     \
         *   / \            /  \                                     \
         *  N   cn   -->   P    S                                    \
         *       \        /      \                                   \
         *        S      N        Dn                                 \
         *         \                                                 \
         *          Dn                                               \
         */                                                          \
        TROTATE(t, sibling, left, right); \
        sibling = parent->right; \
      } \
      /* Trường hợp 4 - Xoay trái ở parent + đảo mầu các nút         \
       * (p và cn có thể có mầu bất kỳ trước khi xoay. Sau khi xoay  \
       * p và dn được tô mầu đen, s có mầu của p,                    \
       * còn cn giữ nguyênmầu của nó)                                \
       *                                                             \
       *      (p)             (s)                                    \
       *      / \             / \                                    \
       *     N   S     -->   P   Dn                                  \
       *        / \         / \                                      \
       *      (cn) dn      N  (cn)                                   \
       */ \
      dn = sibling->right; \
      TROTATE(t, parent, right, left); \
      TPAINT(sibling, TCOLOR_OF(parent)); \
      TPAINT_BLACK(parent); \
      TPAINT_BLACK(dn); \
      break
      ERASE_COLOR_SYMMETRY(left, right);
    } else {
      sibling = parent->left;
      ERASE_COLOR_SYMMETRY(right, left);
#undef ERASE_COLOR_SYMMETRY
    }
  }
}

static struct tmap *tdelete(struct tmap *t, struct tnode *dn) {
  struct tnode *node = dn;
  struct tnode *child = node->right,
            *tmp = node->left,
            *parent, *rebalance;
  struct tnode *p;
  enum tcolors c;
  if (!tmp) {
    /* Trường hợp 1: Nếu nút đang xóa có không quá 1 nút con (dễ)
     *
     * Nếu có một con thì nút con phải là nút đỏ do tính chất 5,
     * và nó phải là nút đen theo tính chất 4. Chúng ta điều chỉnh
     * mầu trong lân cận để tránh gọi hàm sửa mầu sau này.
     */
    p = node->top;
    c = TCOLOR_OF(node);
    parent = p;
    TCHANGE(node, child, parent, t);
    if (child) {
      TSET_PC(child, p, c);
      rebalance = NULL;
    } else {
      rebalance = c == BLACK? parent: NULL;
    }
    tmp = parent;
  } else if (!child) {
    // Vẫn trường hợp 1 nhưng nút con là node->left
    p = node->top;
    c = TCOLOR_OF(node);
    TSET_PC(tmp, p, c);
    parent = p;
    TCHANGE(node, tmp, parent, t);
    rebalance = NULL;
    tmp = parent;
  } else {
    struct tnode *successor = child, *child2;
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
      child->top = successor;
    }
    tmp = node->left;
    successor->left = tmp;
    tmp->top = successor;
    p = node->top;
    c = TCOLOR_OF(node);
    tmp = p;
    TCHANGE(node, successor, tmp, t);
    if (child2) {
      TSET_PC(child2, parent, BLACK);
      rebalance = NULL;
    } else {
      enum tcolors c2 = TCOLOR_OF(successor);
      rebalance = c2 == BLACK? parent: NULL;
    }
    TSET_PC(successor, p, c);
    tmp = successor;
  }
  if (rebalance) {
    tdelete_fixup(t, rebalance);
  }
  free(dn);
  return t;
}

struct tmap *tremove(struct tmap *t, gtype key) {
  struct tnode *n = tsearch(t, &key);
  if (!n) {
    return NULL;
  }
  if (t->fk) {
    t->fk(&n->key);
  }
  if (t->fv) {
    t->fv(&n->value);
  }
  tdelete(t, n);
  --(t->size);
  return t;
}

long tsize(const struct tmap *t) {
  return t->size;
}

gtype *tvalue(gtype *key) {
  return &((struct tnode*)key)->value;
}

struct tnode *tlmost(struct tnode *n) {
  if (!n) {
    return NULL;
  }
  while (n->left != NULL) {
    n = n->left;
  }
  return n;
}

struct tnode *troot(struct tmap *t) {
  return t->root;
}

struct tnode *tnextin(struct tnode *x)  {
  if (!x) {
    return NULL;
  }
  struct tnode *y;
  if (x->right != NULL) {
    y = tlmost(x->right);
  } else {
    y = x->top;
    while (y != NULL && x == y->right) {
      x = y;
      y = y->top;
    }
  }
  return y;
}

void tnext(gtype **k, gtype **v) {
  struct tnode *n = (struct tnode *)(*k);
  struct tnode *tmp = tnextin(n);
  if (!tmp) {
    *k = NULL;
    *v = NULL;
    return;
  }
  *k = &tmp->key;
  *v = &tmp->value;
}
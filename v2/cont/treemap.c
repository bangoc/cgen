/* (C) Nguyễn Bá Ngọc 2023 */
/**
 * @file 
 * @brief Triển khai cấu trúc tra cứu dựa trên
 * cây đỏ đen với khóa và giá trị có kiểu \ref gtype.
 */

#include "cont/treemap.h"

#include <stdlib.h>

/** Các giá trị mầu của nút.
 *  đỏ = 0, đen = 1 như vậy chúng ta có 
 * tổng giá trị mầu = số lượng nút đen
 */
enum tmcolors {
  TMRED = 0,
  TMBLACK = 1
};

/**
 * Cấu trúc nút của treemap, là mở rộng nút của cây đỏ đen.
 * tmnode = Red-black tree map node
 *
 * \private Người sử dụng không cần thao tác với kiểu này.
 */
struct tmnode {
  /** Khóa */
  gtype key;

  /** Giá trị */
  gtype value;
  
  /** Mầu của nút */
  enum tmcolors color;

  /** Con trỏ tới nút con trái */
  struct tmnode *left;

  /** Nút con phải */
  struct tmnode *right;

  /** Nút đỉnh */
  struct tmnode *top;
};

struct tmnode *tmnode(const gtype key, const gtype value) {
  struct tmnode *tmp = malloc(sizeof(struct tmnode));
  if (!tmp) {
#ifdef CGEN_DEBUG
    FLOG("Không thể cấp phát bộ nhớ cho nút.");
#endif  // CGEN_DEBUG
    return NULL;
  }
  tmp->key = key;
  tmp->value = value;
  tmp->color = TMRED;
  tmp->left = tmp->right = tmp->top = NULL;
  return tmp;
}

/**
 * Cấu trúc điều khiển của bảng cây treemap, được tạo bằng hàm
 * treemap = red black map tree
 *
 * rbm_create(gtype_cmp_t cmp, gtype_free_t free_key, gtype_free_t free_value).
 *
 * Các macro hỗ trợ:
 * 
 *   #TMTRAVERSE(k, v, map) - Duyệt tuần tự các cặp trong map.
 */
struct treemap {
  struct tmnode *root;
  gtype_cmp_t cmp;
  gtype_free_t fk, fv;
  long size;
};

struct treemap *tcreate(gtype_cmp_t cmp) {
  if (!cmp) {
#ifdef CGEN_DEBUG
    FLOG("Không thể tạo bảng cây nếu không biết hàm so sánh.");
    return NULL;
#endif  // CGEN_DEBUG    
  }
  struct treemap *t = malloc(sizeof(struct treemap));
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
    struct tmnode *_y = (x)->right; \
    (x)->right = _y->left; \
    if (_y->left != NULL) { \
      _y->left->top = (x); \
    } \
    _y->top = (x)->top; \
    TCHANGE(x, _y, (x)->top, t); \
    _y->left = (x); \
    (x)->top = _y; \
  } while (0)

static void tfixup(struct treemap *t, struct tmnode *n, struct tmnode *p) {
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
      struct tmnode *_u = p->top->right; \
      if (_u->color == TMRED) { \
        /*     GP                gp  <- n mới                      \
             p   u  thành>>>   P    U                              \
          ->n <-     có thể vi phạm tính chất 4 nếu gp->top là đỏ,\
                     n có thể là con trái hoặc con phải của p     \
         */ \
        p->color = TMBLACK; \
        _u->color = TMBLACK; \
        p->top->color = TMRED; \
        n = p->top; \
        p = n->top; \
        if (p == NULL) { \
          /* n là gốc của cây */ \
          n->color = TMBLACK; \
          break; \
        } \
        if (p->color == TMBLACK) { \
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
        p->color = TMBLACK; \
        p->top->color = TMRED; \
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

gtype *tinsert(struct treemap *t, const gtype key, const gtype value) {
  struct tmnode *nn = tmnode(key, value);
  if (!nn) {
#ifdef CGEN_DEBUG
    FLOG("Không thể tạo nút mới.");
    return NULL;
#endif  // CGEN_DEBUG    
  }
  struct tmnode *top = NULL;
  struct tmnode *x = t->root;
  struct tmnode **loc = &t->root;
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
  if (top == NULL) {
    nn->color = TMBLACK;
  } else if (top->color == TMRED) {
    /* Vi phạm tính chất 4 (sau thao tác thêm vào chỉ có tính chất 4
       có thể bị vi phạm). */
    tfixup(t, nn, top);
  }
  return NULL;
}
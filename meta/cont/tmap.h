/* (C) Nguyễn Bá Ngọc 2023 */

#ifndef CONT_TMAP_H_
#define CONT_TMAP_H_

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
  destructor_fnt fk, fv; \
  long size; \
}

#define TCOLOR_OF(n) ((n)? (n)->color: BLACK)
#define TIS_RED(n) (TCOLOR_OF(n) == RED)
#define TIS_BLACK(n) (TCOLOR_OF(n) == BLACK)
#define TPAINT_BLACK(n) ((n)->color = BLACK)
#define TPAINT_RED(n) ((n)->color = RED)
#define TPAINT(n, c) ((n)->color = (c))
#define TSET_PC(n, p, c) (n)->top = (p); TPAINT(n, c)
#define TKEY(n) ((n)->key)
#define TVALUE(n) ((n)->value)
#define TLEFT(n) ((n)->left)
#define TRIGHT(n) ((n)->right)
#define TTOP(n) ((n)->top)
#define TSIZE(t) ((t)->size)
#define TROOT(t) ((t)->root)
#define TFK(t) ((t)->fk)
#define TFV(t) ((t)->fv)
#define TLEFT_MOST(n) TNODE_MATCH(n, left_most)(n)
#define TRIGHT_MOST(n) TNODE_MATCH(n, right_most)(n)
#define TLEFT_DEEPEST(n) TNODE_MATCH(n, left_deepest)(n)
#define TNEXT_LRN(n) TNODE_MATCH(n, next_lrn)(n)
#define TNEXT_LNR(n) TNODE_MATCH(n, next_lnr)(n)
#define TPREV_LNR(n) TNODE_MATCH(n, prev_lnr)(n)
#define TFIRST_LRN(t) TMATCH(t, first_lrn)(t)
#define TFIRST_LNR(t) TMATCH(t, first_lnr)(t)
#define TLAST_LNR(t) TMATCH(t, last_lnr)(t)
#define TCONSTRUCT(tname, objname, ...) \
  struct tname *objname = TMATCH((struct tname *)NULL, create)(__VA_ARGS__)
#define TPUT(t, k, v) TMATCH(t, put)(t, k, v)
#define TGET(t, k) TMATCH(t, get)(t, k)
#define TREMOVE(t, k) TMATCH(t, remove)(t, k)
#define TFREE(t) TMATCH(t, free)(t)

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
struct tname *prefix##create(compare_fnt cmp); \
vtype *prefix##put(struct tname *t, ktype key, vtype value); \
vtype *prefix##get(struct tname *t, ktype key); \
struct tname *prefix##remove(struct tname *t, ktype key); \
void prefix##free(void *po)

#define TSEARCH(t, key, x)  \
do { \
  int rl; \
  x = t->root; \
  while (x) { \
    rl = t->cmp(&key, &x->key); \
    if (rl == 0) { \
      break; \
    } \
    x = rl < 0? x->left: x->right; \
  } \
} while (0)

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
/*     p                  p               p
         x                   x              r
      l     r <- y        l    rl         x
          rl                            l   rl
*/
#define TROTATE(t, x, right, left, y_) \
  do { \
    y_ = (x)->right; \
    (x)->right = y_->left; \
    if (y_->left != NULL) { \
      y_->left->top = (x); \
    } \
    y_->top = (x)->top; \
    TCHANGE(x, y_, (x)->top, t); \
    y_->left = (x); \
    (x)->top = y_; \
  } while (0)

#define IMPL_INSERT_FIXUP(t, n, p, left, right, y_) \
      if (TIS_RED(p->top->right)) { \
        /*     GP                gp  <- n mới
             p   u  thành>>>   P    U
          ->n <-     có thể vi phạm tính chất 4 nếu gp->top là đỏ,
                     n có thể là con trái hoặc con phải của p
         */ \
        TPAINT_BLACK(p); \
        TPAINT_BLACK(p->top->right); \
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
          /*     GP                  GP
               p    U  thành>>>   n <-p  U
                n               p  <-n mới
           */ \
          TROTATE(t, p, right, left, y_); \
          n = p; \
          p = n->top; \
        } \
        /*
         + n là con trái của p
                GP                   gp
             p     U  lật mầu >>   P   U
           n                      n
          >>> & sau khi xoay phải ở GP thành =>>>
              P
            n    gp
                    U
            Thỏa mãn các tính chất của cây đỏ đen
         */ \
        TPAINT_BLACK(p); \
        TPAINT_RED(p->top); \
        p = p->top; \
        TROTATE(t, p, left, right, y_); \
        break;  \
      }

#define TPUT_FIXUP(t, n, p, y_) \
do { \
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
   */ \
  while (1) { \
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
    if (p == p->top->left) { \
      IMPL_INSERT_FIXUP(t, n, p, left, right, y_) \
    } else { \
       IMPL_INSERT_FIXUP(t, n, p, right, left, y_) \
    } \
  } \
} while (0)

#define ERASE_COLOR_SYMMETRY(left, right, p, n, s, cn, dn, u_) \
      /* Trong các ký hiệu cây chữ cái đầu viết thường là nút đỏ,
       *    chữ cái đầu viết hoa là nút đen,
       *    nút được để trong ngoặc có thể là đỏ hoặc đen.
      */ \
      if (TIS_RED(s)) { \
        /*
         * Trường hợp 1 - Xoay trái ở p
         *
         *     P               S
         *    / \             / \
         *   N   s    -->    p   Dn
         *      / \         / \
         *     Cn  Dn      N   Cn <- sibling mới
         */ \
        TROTATE(t, p, right, left, u_); \
        TPAINT_RED(p); \
        TPAINT_BLACK(s); \
        s = p->right; \
      } \
      dn = s->right; \
      if (TIS_BLACK(dn)) { \
        cn = s->left; \
        if (TIS_BLACK(cn)) { \
          /*
           * Trường hợp 2 - Đảo mầu sibling, p có thể có mầu bất kỳ
           *
           *    (p)           (p)
           *    / \           / \
           *   N   S    -->  N   s
           *      / \           / \
           *     Cn  Dn        Cn  Dn
           *
           * Điều này dẫn tới vi phạm ràng buộc 5), vi phạm này có
           * thể được khắc phục bằng cách đảo mầu p thành đen nếu nó
           * là nút đỏ, hoặc đệ quy tại p nếu ngược lại. Nút p có
           * mầu đỏ sau khi xử lý trường hợp 1.
           */ \
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
        /*
         * Trường hợp 3 - Xoay phải tại sibling (p có thể có mầu bất
         * kỳ)
         *
         *              (p)           (p)
         *              / \           / \
         *             N   S    -->  N   cn
         *                / \             \
         *               cn  Dn            S
         *                                  \
         *                                   Dn
         * Lưu ý: + p có thể là nút đỏ, và nếu như vậy thì cả p và
         * Cn đều là các nút đỏ sau khi xoay (vi phạm ràng buộc 4).
         *
         * + Đường đi từ p qua cn sau đó rẽ về phía N bị giảm một
         * nút đen (S, vi phạm tính chất 5).
         *
         * Các vấn đề  này được xử lý trong trường hợp 4: Sau khi
         * xoay trái tại parent, cn được tô bằng mầu của p, dn và p
         * được tô mầu đen)
         *
         *   (p)            (cn)
         *   / \            /  \
         *  N   cn   -->   P    S
         *       \        /      \
         *        S      N        Dn
         *         \
         *          Dn
         */ \
        TROTATE(t, s, left, right, u_); \
        s = p->right; \
      } \
      /* Trường hợp 4 - Xoay trái ở parent + đảo mầu các nút
       * (p và cn có thể có mầu bất kỳ trước khi xoay. Sau khi xoay
       * p và dn được tô mầu đen, s có mầu của p,
       * còn cn giữ nguyênmầu của nó)
       *
       *      (p)             (s)
       *      / \             / \
       *     N   S     -->   P   Dn
       *        / \         / \
       *      (cn) dn      N  (cn)
       */ \
      dn = s->right; \
      TROTATE(t, p, right, left, u_); \
      TPAINT(s, TCOLOR_OF(p)); \
      TPAINT_BLACK(p); \
      TPAINT_BLACK(dn); \
      break

#define TDELETE_FIXUP(t, p, n, s, cn, dn, u_) \
do { \
  /*n - node, s - sibling, cn - close nephew, dn - distant nephew */\
  n = NULL; \
  while (1) { \
    /*
    * Các tính chất bất biến trong vòng lặp:
    * - n là nút đen (hoặc NULL trong lần lặp đầu tiên)
    * - n không phải là nút gốc (top của nó khác NULL)
    * - Tất cả các đường dẫn tới lá đi qua p va n có số
    *   lượng nút đen ít hơn 1 so với các đường dẫn khác.
    */ \
    s = p->right; \
    if (n != s) {  /* n == p->left */ \
      ERASE_COLOR_SYMMETRY(left, right, p, n, s, cn, dn, u_); \
    } else { \
      s = p->left; \
      ERASE_COLOR_SYMMETRY(right, left, p, n, s, cn, dn, u_); \
    } \
  } \
} while (0)

#define TIMPL(tname, ktype, vtype, prefix) \
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
  t->fv = t->fk = NULL; \
  t->size = 0; \
  return t; \
} \
static struct tname *prefix##delete(struct tname *t, struct TNN(tname) *dn) { \
  struct TNN(tname) *node = dn; \
  struct TNN(tname) *child = node->right, \
            *tmp = node->left, \
            *parent, *rebalance; \
  struct TNN(tname) *p; \
  enum tcolors c; \
  if (!tmp) { \
    /* Trường hợp 1: Nếu nút đang xóa có không quá 1 nút con (dễ)
     *
     * Nếu có một con thì nút con phải là nút đỏ do tính chất 5,
     * và nó phải là nút đen theo tính chất 4. Chúng ta điều chỉnh
     * mầu trong lân cận để tránh gọi hàm sửa mầu sau này.
     */ \
    p = node->top; \
    c = TCOLOR_OF(node); \
    parent = p; \
    TCHANGE(node, child, parent, t); \
    if (child) { \
      TSET_PC(child, p, c); \
      rebalance = NULL; \
    } else { \
      rebalance = c == BLACK? parent: NULL; \
    } \
    tmp = parent; \
  } else if (!child) { \
    /* Vẫn trường hợp 1 nhưng nút con là node->left */ \
    p = node->top; \
    c = TCOLOR_OF(node); \
    TSET_PC(tmp, p, c); \
    parent = p; \
    TCHANGE(node, tmp, parent, t); \
    rebalance = NULL; \
    tmp = parent; \
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
      parent = successor; \
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
        parent = successor; \
        successor = tmp; \
        tmp = tmp->left; \
      } while (tmp); \
      child2 = successor->right; \
      parent->left = child2; \
      successor->right = child; \
      child->top = successor; \
    } \
    tmp = node->left; \
    successor->left = tmp; \
    tmp->top = successor; \
    p = node->top; \
    c = TCOLOR_OF(node); \
    tmp = p; \
    TCHANGE(node, successor, tmp, t); \
    if (child2) { \
      TSET_PC(child2, parent, BLACK); \
      rebalance = NULL; \
    } else { \
      enum tcolors c2 = TCOLOR_OF(successor); \
      rebalance = c2 == BLACK? parent: NULL; \
    } \
    TSET_PC(successor, p, c); \
    tmp = successor; \
  } \
  if (rebalance) { \
    struct TNN(tname) *n, *s, *cn, *dn, *u_; \
    TDELETE_FIXUP(t, rebalance, n, s, cn, dn, u_); \
  } \
  free(dn); \
  return t; \
} \
vtype *prefix##put(struct tname *t, ktype key, vtype value) { \
  struct TNN(tname) *nn = TNN(tname)(key, value); \
  struct TNN(tname) *top = NULL; \
  struct TNN(tname) *x = t->root; \
  struct TNN(tname) **loc = &t->root; \
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
    struct TNN(tname) *y_; \
    TPUT_FIXUP(t, nn, top, y_); \
  } \
  ++t->size; \
  return NULL; \
} \
vtype *prefix##get(struct tname *t, ktype key) { \
  struct TNN(tname) *x; \
  TSEARCH(t, key, x); \
  if (!x) { \
    return NULL; \
  } \
  return &x->value; \
} \
struct tname *prefix##remove(struct tname *t, ktype key) { \
  struct TNN(tname) *n; \
  TSEARCH(t, key, n); \
  if (!n) { \
    return NULL; \
  } \
  if (t->fk) { \
    t->fk(&n->key); \
  } \
  if (t->fv) { \
    t->fv(&n->value); \
  }\
  prefix##delete(t, n);\
  --(t->size); \
  return t; \
} \
void prefix##free(void *po) { \
  struct tname *t = po; \
  struct TNN(tname) *n = prefix##first_lrn(t); \
  struct TNN(tname) *tmp = NULL; \
  while (n) { \
    if (t->fk) { \
      t->fk(&n->key); \
    } \
    if (t->fv) { \
      t->fv(&n->value); \
    } \
    tmp = n; \
    n = prefix##next_lrn(n); \
    free(tmp); \
  } \
  free(t); \
}

#endif  // CONT_TMAP_H_
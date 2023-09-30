/* (C) Nguyen Ba Ngoc 2022 */

#include "tree/rb.h"

const char * color_names[] = {"Đỏ", "Đen"};

struct rbnode *rb_create_node() {
  struct bnnode *tmp = bn_create_node();
  struct rbnode *nn = realloc(tmp, sizeof(struct rbnode));
  nn->color = RB_RED;
  return nn;
}

static void rb_insert_fixup(struct bntree *t, struct bnnode *n, struct bnnode *p) {
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
  while (true) {
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
      struct bnnode *_u = p->top->right; \
      if (rb_is_red(_u)) { \
        /*     GP                gp  <- n mới                      \
             p   u  thành>>>   P    U                              \
          ->n <-     có thể vi phạm tính chất 4 nếu gp->top là đỏ,\
                     n có thể là con trái hoặc con phải của p     \
         */ \
        rb_set_black(p); \
        rb_set_black(_u); \
        rb_set_red(p->top); \
        n = p->top; \
        p = n->top; \
        if (p == NULL) { \
          /* n là gốc của cây */ \
          rb_set_black(n); \
          break; \
        } \
        if (rb_is_black(p)) { \
          /* Các tính chất đã được thỏa mãn */ \
          break; \
        } \
      } else { \
        if (n == n->top->right) { \
          /*     GP                  GP           \
               p    U  thành>>>   n <-p  U        \
                n               p  <-n mới        \
           */ \
          bn_rotate(t, p, right, left); \
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
        rb_set_color(p, RB_BLACK); \
        rb_set_color(p->top, RB_RED); \
        p = p->top; \
        bn_rotate(t, p, left, right); \
        break;  \
      }
      IMPL_INSERT_FIXUP(left, right)
    } else {
      IMPL_INSERT_FIXUP(right, left)
    }
  }
}

#undef IMPL_INSERT_FIXUP

#define RB_INSERT_TPL(bs_interface, ...) \
  struct bs_ires ires = bs_interface(t, nn, cmp); \
  __VA_ARGS__ \
  struct bnnode *par = bn_node(nn)->top; \
  if (par == NULL) { \
    rb_set_black(nn); \
  } else if (rb_is_red(par)) { \
    /* vi phạm tính chất 4 (sau thao tác thêm vào chỉ có tính chất 4) \
       có thể bị vi phạm. */ \
    rb_insert_fixup(bn_tree(t), bn_node(nn), bn_node(par)); \
    /* Tìm vị trí */ \
  } \
  return ires

struct bs_ires __rb_insert(struct bntree *t, struct rbnode *nn, bn_compare_t cmp) {
  RB_INSERT_TPL(bs_insert);
}

struct bs_ires __rb_insert_unique(struct bntree *t, struct rbnode *nn, bn_compare_t cmp) {
  RB_INSERT_TPL(bs_insert_unique,
    if (!ires.inserted) {
      return ires;
    }
  );
}

#undef RB_INSERT_TPL

static void rb_delete_fix_color(struct bntree *t, struct bnnode *parent) {
  struct bnnode *node = NULL, *sibling,
          *cn,  // Con của sibling ở phía gần node (close nephew)
          *dn;  // Con của sibling ở phía xa node (distant nephew)
  while (true) {
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
        bn_rotate(t, parent, right, left); \
        rb_set_red(parent); \
        rb_set_black(sibling); \
        sibling = parent->right; \
      } \
      dn = sibling->right; \
      if (rb_is_black(dn)) { \
        cn = sibling->left; \
        if (rb_is_black(cn)) { \
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
        bn_rotate(t, sibling, left, right); \
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
      bn_rotate(t, parent, right, left); \
      rb_set_color(sibling, rb_color(parent)); \
      rb_set_black(parent); \
      rb_set_black(dn); \
      break
      ERASE_COLOR_SYMMETRY(left, right);
    } else {
      sibling = parent->left;
      ERASE_COLOR_SYMMETRY(right, left);
#undef ERASE_COLOR_SYMMETRY
    }
  }
}

#define rb_set_parent_color(n, parent, color) \
  n->top = parent; \
  rb_set_color(n, color)

int __rb_delete(struct bntree *t, struct rbnode *dn) {
  struct bnnode *node = bn_node(dn);
  struct bnnode *child = node->right,
            *tmp = node->left,
            *parent, *rebalance;
  struct bnnode *p;
  enum rbnode_color c;
  if (!tmp) {
    /* Trường hợp 1: Nếu nút đang xóa có không quá 1 nút con (dễ)
     *
     * Nếu có một con thì nút con phải là nút đỏ do tính chất 5,
     * và nó phải là nút đen theo tính chất 4. Chúng ta điều chỉnh
     * mầu trong lân cận để tránh gọi hàm sửa mầu sau này.
     */
    p = node->top;
    c = rb_color(node);
    parent = p;
    bn_change_child(node, child, parent, t);
    if (child) {
      rb_set_parent_color(child, p, c);
      rebalance = NULL;
    } else {
      rebalance = c == RB_BLACK? parent: NULL;
    }
    tmp = parent;
  } else if (!child) {
    // Vẫn trường hợp 1 nhưng nút con là node->left
    p = node->top;
    c = rb_color(node);
    rb_set_parent_color(tmp, p, c);
    parent = p;
    bn_change_child(node, tmp, parent, t);
    rebalance = NULL;
    tmp = parent;
  } else {
    struct bnnode *successor = child, *child2;
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
    c = rb_color(node);
    tmp = p;
    bn_change_child(node, successor, tmp, t);
    if (child2) {
      rb_set_parent_color(child2, parent, RB_BLACK);
      rebalance = NULL;
    } else {
      enum rbnode_color c2 = rb_color(successor);
      rebalance = c2 == RB_BLACK? parent: NULL;
    }
    rb_set_parent_color(successor, p, c);
    tmp = successor;
  }
  if (rebalance) {
    rb_delete_fix_color(t, rebalance);
  }
  free(dn);
  return 1;
}

#undef rb_set_parent_color

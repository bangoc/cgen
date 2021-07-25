#include "s2i.h"

int main() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  s2i_insert(t, "Một", 1);
  s2i_insert(t, "Hai", 2);
  s2i_insert(t, "Ba", 3);
  s2i_insert(t, "Bốn", 4);
  s2i_insert(t, "Năm", 5);
  s2i_insert(t, "Sáu", 6);
  s2i_insert(t, "Bẩy", 7);
  s2i_insert(t, "Tám", 8);
  s2i_insert(t, "Tám", 18);
  s2i_insert(t, "Tám", 28);
  s2i_insert(t, "Chín", 9);
  s2i_insert(t, "Mười", 10);
  bn_pprint(t, s2i_print_node);
  /* Trùng lặp khóa:
   *             (Tám, 28) - Đỏ
   *          (Tám, 18) - Đen
   *       (Tám, 8) - Đen
   *           (Sáu, 6) - Đen
   *     (Năm, 5) - Đen
   *           (Một, 1) - Đen
   *             (Mười, 10) - Đỏ
   *        (Hai, 2) - Đen
   *                (Chín, 9) - Đỏ
   *              (Bốn, 4) - Đen
   *          (Bẩy, 7) - Đỏ
   *              (Ba, 3) - Đen
   * Không trùng lặp khóa:
   *              (Tám, 8) - Đỏ
   *           (Sáu, 6) - Đen
   *        (Năm, 5) - Đỏ
   *           (Một, 1) - Đen
   *              (Mười, 10) - Đỏ
   *     (Hai, 2) - Đen
   *              (Chín, 9) - Đỏ
   *           (Bốn, 4) - Đen
   *        (Bẩy, 7) - Đỏ
   *           (Ba, 3) - Đen
   * Đối với cấu trúc tra cứu thì khóa phải là duy nhất.
   */
  s2i_free(&t);
  return 0;
}
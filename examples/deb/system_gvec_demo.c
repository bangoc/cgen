/* (C) Nguyễn Bá Ngọc 2022 */

/** @file
 * @brief Minh họa kịch bản sử dụng thư viện cgen sau khi cài như thư viện tiêu chuẩn.
 * Có thể biên dịch chương trình với lệnh:
 *   gcc -o prog system_gvec_demo.c -lbkcgen
 */

#include <bkcgen.h>

#include <stdio.h>

int main() {
  struct gvector *v = gvec_create(0, NULL);
  gvec_append(v, gtype_l(1));
  gvec_append(v, gtype_l(3));
  gvec_append(v, gtype_l(5));
  gvec_pprint(v, gtype_print_l);
  gvec_free(v);
  return 0;
}
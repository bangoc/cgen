/* (C) Nguyễn Bá Ngọc 2022 */

/** @file
 * @brief Minh họa kịch bản sử dụng thư viện cgen sau khi cài như thư viện tiêu chuẩn.
 * Có thể biên dịch chương trình với lệnh:
 *   gcc -o prog system_gvec_demo.c -lbkcgen
 */

#include <bkcgen.h>

#include <stdio.h>

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create(0, NULL);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create(0);
#endif  // CGEN_USE_GC
  gvec_append(v, gtype_l(1));
  gvec_append(v, gtype_l(3));
  gvec_append(v, gtype_l(5));
  gvec_pprint(v, gtype_print_l);
#ifndef CGEN_USE_GC
  gvec_free(v);
#endif  // CGEN_USE_GC
  return 0;
}
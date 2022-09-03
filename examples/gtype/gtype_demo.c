/* (C) Nguyen Ba Ngoc 2022 */

/**
 * gtype là 1 union - nhóm kiểu,
 * chúng ta có thể sử dụng đối tượng kiểu gtype để lưu
 * các giá trị thuộc các kiểu khác nhau: Số nguyên,
 * số thực và nhiều kiểu con trỏ khác nhau.
 */

#include "all.h"

#include <stdio.h>

int main() {
  printf("sizeof(gtype) = %zu\n", sizeof(gtype));
  long l = 10;
  double d = 3.14;
  char *s = "Hello world!";
  void *v;
  gtype tmp;
  gtype value;
  value = gtype_l(l);
  value = gtype_d(d);
  value = gtype_s(s);
  value = gtype_v(v);
  value = gtype_g(&tmp);

  gdl_t gdl;
  gsl_t gsl;
  gvec_t gvec;
  hmap_t hmap;
  hset_t hset;
  p1w_t p1w;
  p2w_t p2w;
  rbm_t rbm;
  rbs_t rbs;
  value = gtype_gdl(gdl);
  value = gtype_gsl(gsl);
  value = gtype_gvec(gvec);
  value = gtype_hmap(hmap);
  value = gtype_hset(hset);
  value = gtype_p1w(p1w);
  value = gtype_p2w(p2w);
  value = gtype_rbm(rbm);
  value = gtype_rbs(rbs);

  return 0;
}
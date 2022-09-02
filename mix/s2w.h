#ifndef MIX_S2W_H_
#define MIX_S2W_H_

/* (C) Nguyen Ba Ngoc 2022 */

#include "dab/gvec.h"
#include "tree/spec/s2i.h"

/**
 * Các chỉ số được tăng dần tự động 0, 1, ...
 * quy ước -1 là chỉ số không hợp lệ.
 */

typedef struct string_index_2way{
  gvec_t is;
  rbm_t si;
} s2w_s, *s2w_t;

s2w_t s2w_create();
long *s2w_put(s2w_t col, const char *s);
int s2w_remove(s2w_t col, const char *s);
long s2w_id(s2w_t col, const char *s);
char *s2w_str(s2w_t col, const long id);
void s2w_free(s2w_t col);

#endif  // MIX_S2W_H_
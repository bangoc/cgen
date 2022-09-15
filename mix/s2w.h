#ifndef MIX_S2W_H_
#define MIX_S2W_H_

/* (C) Nguyen Ba Ngoc 2022 */

#include "vec/gvec.h"
#include "tree/spec/s2i.h"

/**
 * Cấu trúc điều khiển của ánh xạ 2 chiều chuỗi <=> chỉ số nguyên.
 * Các chỉ số được tăng dần tự động 0, 1, ...
 * quy ước -1 là chỉ số không hợp lệ.
 */
struct s2w {
  struct gvector *is;
  struct rbm *si;
};

struct s2w *s2w_create();
struct rbm_ires s2w_insert(struct s2w *col, const char *s);
long *s2w_put(struct s2w *col, const char *s);
int s2w_remove(struct s2w *col, const char *s);
long s2w_id(struct s2w *col, const char *s);
char *s2w_str(struct s2w *col, const long id);
void s2w_free(struct s2w *col);

#endif  // MIX_S2W_H_
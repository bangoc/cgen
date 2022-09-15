#ifndef MIX_S2W_H_
#define MIX_S2W_H_

/* (C) Nguyen Ba Ngoc 2022 */

#include "vec/gvec.h"
#include "tree/spec/s2i.h"

/**
 * Cấu trúc điều khiển của ánh xạ 2 chiều chuỗi <=> chỉ số nguyên.
 * Các chỉ số được tăng dần tự động 0, 1, ...
 * quy ước -1 là chỉ số không hợp lệ.
 * si2ways = string id 2 ways (mapping)
 */
struct si2ways {
  struct gvector *is;
  struct rbmtree *si;
};

struct si2ways *s2w_create();
struct rbm_ires s2w_insert(struct si2ways *col, const char *s);
long *s2w_put(struct si2ways *col, const char *s);
int s2w_remove(struct si2ways *col, const char *s);
long s2w_id(struct si2ways *col, const char *s);
char *s2w_str(struct si2ways *col, const long id);
void s2w_free(struct si2ways *col);

#endif  // MIX_S2W_H_
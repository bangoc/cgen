/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef TM_H_
#define TM_H_

#include "rb.h"
#include "gtype.h"

typedef struct tn_s {
  struct rb_node rb_node;
  gtype key, value;
} *tnt;

typedef struct tm_s {
  struct bn_tree t;
  bn_compare_t cmp;
} *tmt;

// ========== Khai báo hàm ===============

tnt tm_create_node(gtype key, gtype value);
tmt tm_create(bn_compare_t cmp);

// Nếu đã có khóa thì bỏ qua và trả về nút tương ứng với khóa
tnt tm_insert(tmt t, gtype key, gtype value);
gtype *tm_value(tmt t, gtype key);
tnt tm_search(tmt t, gtype key);
tnt tm_delete(tmt t, gtype key);


// ========== Macro viết nhanh ===========

#define to_tm(n) ((tnt)n)
#define tm_node_key(n) to_tm(n)->key
#define tm_node_value(n) to_tm(n)->value


#endif  // TM_T_

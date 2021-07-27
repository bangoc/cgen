#ifndef GTTREESET_H_
#define GTTREESET_H_

/*
 TODO: Tiếp tục xây dựng cấu trúc tập hợp dựa trên cây đỏ đen khi có nhu cầu
*/


#include "gtype.h"
#include "rb.h"

#include <stdlib.h>

typedef struct treeset_node {
  struct rb_node rb_node;
  gtype elem;
} *treeset_node_t;

// ========== Khai báo hàm ===============
static bn_node_t ts_create_node(gtype data);

// ========== Macro viết nhanh ===========

#define to_ts(n) ((treeset_node_t)n)
#define ts_node_elem(n) to_ts(n)->elem

// ========== Định nghĩa hàm =============

#endif  // GTTREESET_H_
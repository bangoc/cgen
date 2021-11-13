/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef P2W_H_
#define P2W_H_

#include "arr.h"
#include "gtype.h"

#include <stdbool.h>

typedef struct p2wheap {
    long size;
    arr_t(gtype) data;
    arr_t(gtype) index;
    arr_t(gtype) index2;
} *p2wheap_t;

#define PARENT(x)   (((x)+1)/2-1)
#define LEFTCHILD(x)  (((x)+1)*2-1)
#define RIGHTCHILD(x) (((x)+1)*2)

// ========== Khai báo hàm ===============

p2wheap_t p2w_create();
void p2w_free(p2wheap_t *h);
long p2w_size(const p2wheap_t h);
int p2w_clear(p2wheap_t h);
bool p2w_empty(const p2wheap_t h);
int p2w_push_with_index(p2wheap_t h, long idx, gtype elem, gtype_cmp_t cmp);
gtype p2w_max(const p2wheap_t h);
long p2w_max_index(const p2wheap_t h);
gtype p2w_get(const p2wheap_t h, long idx);
gtype p2w_delete_max(p2wheap_t h, gtype_cmp_t cmp);
gtype p2w_deactivate_max(p2wheap_t h, gtype_cmp_t cmp);
gtype p2w_delete_max_index(p2wheap_t h, long *idx, gtype_cmp_t cmp);
int p2w_modify(p2wheap_t h, long idx, gtype elem, gtype_cmp_t cmp);
bool p2w_check(p2wheap_t h, gtype_cmp_t cmp);

/* Giao diện cho kiểu double */
// ========== Khai báo hàm ===============

int d2w_push_with_index(p2wheap_t h, long idx, double elem);
double d2w_max(const p2wheap_t h);
double d2w_get(const p2wheap_t h, long idx);
double d2w_delete_max(p2wheap_t h);
double d2w_deactivate_max(p2wheap_t h);
double d2w_delete_max_index(p2wheap_t h, long *idx);
int d2w_modify(p2wheap_t h, long idx, double elem);

#endif  // P2W_H_
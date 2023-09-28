#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

// Khởi tạo cap = n, sz = 0
struct vector *vec_create(int n) {
   struct vector *v = malloc(sizeof(struct vector));
   v->sz = 0;
   v->cap = n;
   v->elems = malloc(n * sizeof(int));
   return v;
}

void vec_free(struct vector *v) {
   free(v->elems);
   free(v);
}

// Đọc
int vec_get(struct vector *v, int idx) { 
  return v->elems[idx];
}

// Cập nhật
void vec_set(struct vector *v, int idx, int value) {
  v->elems[idx] = value;
}

// Kích thước hiện tại
int vec_size(struct vector *v) {  
  return v->sz;
}

// Dung lượng hiện tại
int vec_cap(struct vector *v) {
  return v->cap;
}

// Điều chỉnh bộ nhớ dự phòng
void vec_reserve(struct vector *v, int newcap) {
  // Không giải phóng các phần tử đã sử dụng
  if (newcap <= v->sz) {
    return;
  }
  v->elems = realloc(v->elems, newcap * sizeof(int));
  v->cap = newcap;
}

// Thêm phần tử vào sau phần tử cuối cùng,
// thay đổi dung lượng nếu cần.
void vec_append(struct vector *v, int value) {
  if (v->cap == 0) {
    vec_reserve(v, 16);
  } else if (v->sz == v->cap) {
    vec_reserve(v, 2 * v->cap);
  }
  v->elems[v->sz] = value;
  ++v->sz;
}

// Xuất nội dung của vec-tơ để hỗ trợ gỡ rối
void vec_pprint(struct vector *v) {
  printf("size: %d\n", v->sz);
  printf("cap: %d\n", v->cap);
  printf("elems:");
  for (int i = 0; i < v->sz; ++i) {
    printf(" %d", v->elems[i]);
  }
  printf("\n");
}
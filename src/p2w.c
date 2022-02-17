/*
  (C) Nguyen Ba Ngoc 2021
  Hàng đợi ưu tiên truy cập 2 chiều dựa trên Heap
*/

#include "p2w.h"

#define arr_set_value_with_index(a, v, i) \
  do {\
    if ((i) >= arr_capacity(a)) { \
      arr_set_capacity(a, 2 * (i) + 1); \
    } \
    ARR(a)[(i)] = (v); \
  } while (0)

int p2w_init(p2w_t h) {
  h->size = 0;
  h->data = arr_create(0, gtype);
  h->index = arr_create(0, gtype);
  h->index2 = arr_create(0, gtype);

  return 0;
}

p2w_t p2w_create() {
  p2w_t h = malloc(sizeof(struct priority_two_ways));
  p2w_init(h);
  return h;
}

void gtype_free_p2w(gtype value) {
  p2w_free(value.p2w);
}

long p2w_size(const p2w_t h) {
  return arr_size(h->data);
}

void p2w_switch(p2w_t h, long e1, long e2) {
  if (e1 != e2) {
    long tmp1, tmp2;
    gtype tmp3 = ARR(h->data)[e1];
    ARR(h->data)[e1] = ARR(h->data)[e2];
    ARR(h->data)[e2] = tmp3;

    tmp1 = ARR(h->index)[e1].l;
    tmp2 = ARR(h->index)[e2].l;

    arr_set_value_with_index(h->index2, gtype_l(e2 + 2), tmp1);
    arr_set_value_with_index(h->index2, gtype_l(e1 + 2), tmp2);

    arr_set_value_with_index(h->index, gtype_l(tmp2), e1);
    arr_set_value_with_index(h->index, gtype_l(tmp1), e2);
  }
}

void p2w_shift_up(p2w_t h, long elem, gtype_cmp_t cmp) {
  if (elem == 0 || cmp(ARR(h->data)[elem], ARR(h->data)[PARENT(elem)]) < 0) {
    /* at the top */
  } else {
    p2w_switch(h, elem, PARENT(elem));
    p2w_shift_up(h, PARENT(elem), cmp);
  }
}

void p2w_sink(p2w_t h, long head, gtype_cmp_t cmp) {
  long size = p2w_size(h);
  if (LEFTCHILD(head) >= size) {
    /* no subtrees */
  } else if (RIGHTCHILD(head) == size ||
         cmp(ARR(h->data)[LEFTCHILD(head)], ARR(h->data)[RIGHTCHILD(head)]) >= 0) {
    /* sink to the left if needed */
    if (cmp(ARR(h->data)[head], ARR(h->data)[LEFTCHILD(head)]) < 0) {
      p2w_switch(h, head, LEFTCHILD(head));
      p2w_sink(h, LEFTCHILD(head), cmp);
    }
  } else {
    /* sink to the right */
    if (cmp(ARR(h->data)[head], ARR(h->data)[RIGHTCHILD(head)]) < 0) {
      p2w_switch(h, head, RIGHTCHILD(head));
      p2w_sink(h, RIGHTCHILD(head), cmp);
    }
  }
}

int p2w_clear(p2w_t h) {
  arr_set_size(h->data, 0);
  arr_set_size(h->index, 0);
  arr_set_size(h->index2, 0);
  arr_set_capacity(h->data, 0);
  arr_set_capacity(h->index, 0);
  arr_set_capacity(h->index2, 0);
  h->size = 0;
  return 0;
}

bool p2w_empty(const p2w_t h) {
  return arr_size(h->data) == 0;
}

int p2w_push_with_index(p2w_t h, long idx, gtype elem, gtype_cmp_t cmp) {
  long size = arr_size(h->data);
  arr_append(h->data, elem);
  arr_append(h->index, gtype_l(idx));
  arr_set_value_with_index(h->index2, gtype_l(size + 2), idx);

  p2w_shift_up(h, size, cmp);
  return 0;
}

long p2w_max_size(const p2w_t h) {
  return h->size;
}

gtype p2w_max(const p2w_t h) {
  return ARR(h->data)[0];
}

long p2w_max_index(const p2w_t h) {
  return ARR(h->index)[0].l;
}

bool p2w_has_elem(const p2w_t h, long idx) {
  return ARR(h->index2)[idx].l != 0;
}

bool p2w_has_active(const p2w_t h, long idx) {
  return ARR(h->index2)[idx].l > 1;
}

gtype p2w_get(const p2w_t h, long idx) {
  long i = ARR(h->index2)[idx].l - 2;
  return ARR(h->data)[i];
}

gtype p2w_delete_max(p2w_t h, gtype_cmp_t cmp) {
  gtype tmp = ARR(h->data)[0];
  long tmpidx = ARR(h->index)[0].l;
  p2w_switch(h, 0, p2w_size(h) - 1);
  arr_set_size(h->data, arr_size(h->data) - 1);
  arr_set_size(h->index, arr_size(h->index) - 1);
  arr_set_value_with_index(h->index2, gtype_l(0), tmpidx);
  p2w_sink(h, 0, cmp);

  return tmp;
}

gtype p2w_deactivate_max(p2w_t h, gtype_cmp_t cmp) {
  gtype tmp = ARR(h->data)[0];
  long tmpidx = ARR(h->index)[0].l;
  p2w_switch(h, 0, p2w_size(h) - 1);
  arr_set_size(h->data, arr_size(h->data) - 1);
  arr_set_size(h->index, arr_size(h->index) - 1);
  arr_set_value_with_index(h->index2, gtype_l(1), tmpidx);
  p2w_sink(h, 0, cmp);

  return tmp;
}

gtype p2w_delete_max_index(p2w_t h, long *idx, gtype_cmp_t cmp) {
  gtype tmp = ARR(h->data)[0];
  long tmpidx = ARR(h->index)[0].l;
  p2w_switch(h, 0, p2w_size(h) - 1);
  arr_set_size(h->data, arr_size(h->data) - 1);
  arr_set_size(h->index, arr_size(h->index) - 1);
  arr_set_value_with_index(h->index2, gtype_l(0), tmpidx);
  p2w_sink(h, 0, cmp);

  if (idx) {
    *idx = tmpidx;
  }
  return tmp;
}

int p2w_modify(p2w_t h, long idx, gtype elem, gtype_cmp_t cmp) {
  long pos = ARR(h->index2)[idx].l - 2;

  ARR(h->data)[pos] = elem;
  p2w_sink(h, pos, cmp);
  p2w_shift_up(h, pos, cmp);

  return 0;
}

bool p2w_check(p2w_t h, gtype_cmp_t cmp) {
  long size = p2w_size(h);
  int ecode = 0;
  for (long i = 0; i < size; i++) {
    if (LEFTCHILD(i) >= size) {
      break;
    }
    if (cmp(ARR(h->data)[LEFTCHILD(i)], ARR(h->data)[i]) > 0) {
      ecode = 1;
      break;
    }
    if (RIGHTCHILD(i) >= size) {
      break;
    }
    if (cmp(ARR(h->data)[RIGHTCHILD(i)], ARR(h->data)[i]) > 0) {
      ecode = 1;
      break;
    }
  }

  return ecode == 0;
}

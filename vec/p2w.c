/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Hàng đợi ưu tiên truy cập 2 chiều dựa trên Heap
 */

#include "vec/p2w.h"

#define arr_set_value_with_index(a, v, i) \
  do {\
    if ((i) >= arr_capacity(a)) { \
      arr_set_capacity(a, 2 * (i) + 1); \
    } \
    arr(a)[(i)] = (v); \
  } while (0)

int p2w_init(struct p2ways *h) {
  h->size = 0;
  h->data = arr_create(0, gtype);
  h->index = arr_create(0, gtype);
  h->index2 = arr_create(0, gtype);

  return 0;
}

struct p2ways *p2w_create() {
  struct p2ways *h = malloc(sizeof(struct p2ways));
  p2w_init(h);
  return h;
}

void gtype_free_p2w(gtype value) {
  p2w_free(value.p2w);
}

long p2w_size(const struct p2ways *h) {
  return arr_size(h->data);
}

void p2w_switch(struct p2ways *h, long e1, long e2) {
  if (e1 != e2) {
    long tmp1, tmp2;
    gtype tmp3 = arr(h->data)[e1];
    arr(h->data)[e1] = arr(h->data)[e2];
    arr(h->data)[e2] = tmp3;

    tmp1 = arr(h->index)[e1].l;
    tmp2 = arr(h->index)[e2].l;

    arr_set_value_with_index(h->index2, gtype_l(e2 + 2), tmp1);
    arr_set_value_with_index(h->index2, gtype_l(e1 + 2), tmp2);

    arr_set_value_with_index(h->index, gtype_l(tmp2), e1);
    arr_set_value_with_index(h->index, gtype_l(tmp1), e2);
  }
}

void p2w_shift_up(struct p2ways *h, long elem, gtype_cmp_t cmp) {
  if (elem == 0 || cmp(arr(h->data)[elem], arr(h->data)[PARENT(elem)]) < 0) {
    /* at the top */
  } else {
    p2w_switch(h, elem, PARENT(elem));
    p2w_shift_up(h, PARENT(elem), cmp);
  }
}

void p2w_sink(struct p2ways *h, long head, gtype_cmp_t cmp) {
  long size = p2w_size(h);
  if (LEFTCHILD(head) >= size) {
    /* no subtrees */
  } else if (RIGHTCHILD(head) == size ||
         cmp(arr(h->data)[LEFTCHILD(head)], arr(h->data)[RIGHTCHILD(head)]) >= 0) {
    /* sink to the left if needed */
    if (cmp(arr(h->data)[head], arr(h->data)[LEFTCHILD(head)]) < 0) {
      p2w_switch(h, head, LEFTCHILD(head));
      p2w_sink(h, LEFTCHILD(head), cmp);
    }
  } else {
    /* sink to the right */
    if (cmp(arr(h->data)[head], arr(h->data)[RIGHTCHILD(head)]) < 0) {
      p2w_switch(h, head, RIGHTCHILD(head));
      p2w_sink(h, RIGHTCHILD(head), cmp);
    }
  }
}

int p2w_clear(struct p2ways *h) {
  arr_set_size(h->data, 0);
  arr_set_size(h->index, 0);
  arr_set_size(h->index2, 0);
  arr_set_capacity(h->data, 0);
  arr_set_capacity(h->index, 0);
  arr_set_capacity(h->index2, 0);
  h->size = 0;
  return 0;
}

bool p2w_empty(const struct p2ways *h) {
  return arr_size(h->data) == 0;
}

int p2w_push_with_index(struct p2ways *h, long idx, gtype elem, gtype_cmp_t cmp) {
  long size = arr_size(h->data);
  arr_append(h->data, elem);
  arr_append(h->index, gtype_l(idx));
  arr_set_value_with_index(h->index2, gtype_l(size + 2), idx);

  p2w_shift_up(h, size, cmp);
  return 0;
}

long p2w_max_size(const struct p2ways *h) {
  return h->size;
}

gtype p2w_max(const struct p2ways *h) {
  return arr(h->data)[0];
}

long p2w_max_index(const struct p2ways *h) {
  return arr(h->index)[0].l;
}

bool p2w_has_elem(const struct p2ways *h, long idx) {
  return arr(h->index2)[idx].l != 0;
}

bool p2w_has_active(const struct p2ways *h, long idx) {
  return arr(h->index2)[idx].l > 1;
}

gtype p2w_get(const struct p2ways *h, long idx) {
  long i = arr(h->index2)[idx].l - 2;
  return arr(h->data)[i];
}

gtype p2w_delete_max(struct p2ways *h, gtype_cmp_t cmp) {
  gtype tmp = arr(h->data)[0];
  long tmpidx = arr(h->index)[0].l;
  p2w_switch(h, 0, p2w_size(h) - 1);
  arr_set_size(h->data, arr_size(h->data) - 1);
  arr_set_size(h->index, arr_size(h->index) - 1);
  arr_set_value_with_index(h->index2, gtype_l(0), tmpidx);
  p2w_sink(h, 0, cmp);

  return tmp;
}

gtype p2w_deactivate_max(struct p2ways *h, gtype_cmp_t cmp) {
  gtype tmp = arr(h->data)[0];
  long tmpidx = arr(h->index)[0].l;
  p2w_switch(h, 0, p2w_size(h) - 1);
  arr_set_size(h->data, arr_size(h->data) - 1);
  arr_set_size(h->index, arr_size(h->index) - 1);
  arr_set_value_with_index(h->index2, gtype_l(1), tmpidx);
  p2w_sink(h, 0, cmp);

  return tmp;
}

gtype p2w_delete_max_index(struct p2ways *h, long *idx, gtype_cmp_t cmp) {
  gtype tmp = arr(h->data)[0];
  long tmpidx = arr(h->index)[0].l;
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

int p2w_modify(struct p2ways *h, long idx, gtype elem, gtype_cmp_t cmp) {
  long pos = arr(h->index2)[idx].l - 2;

  arr(h->data)[pos] = elem;
  p2w_sink(h, pos, cmp);
  p2w_shift_up(h, pos, cmp);

  return 0;
}

bool p2w_check(struct p2ways *h, gtype_cmp_t cmp) {
  long size = p2w_size(h);
  int ecode = 0;
  for (long i = 0; i < size; i++) {
    if (LEFTCHILD(i) >= size) {
      break;
    }
    if (cmp(arr(h->data)[LEFTCHILD(i)], arr(h->data)[i]) > 0) {
      ecode = 1;
      break;
    }
    if (RIGHTCHILD(i) >= size) {
      break;
    }
    if (cmp(arr(h->data)[RIGHTCHILD(i)], arr(h->data)[i]) > 0) {
      ecode = 1;
      break;
    }
  }

  return ecode == 0;
}

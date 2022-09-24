/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Hàng đợi ưu tiên truy cập 2 chiều dựa trên Heap
 */

#include "vec/p2w.h"

#define arr_set_value_with_index(a, v, i) \
  do {\
    if ((i) >= arr_capacity(a)) { \
      arr_reserve(a, (i) + 1); \
    } \
    (a)[(i)] = (v); \
  } while (0)

struct p2ways *p2w_create(gtype_cmp_t cmp) {
  struct p2ways *h = malloc(sizeof(struct p2ways));
  h->data = arr_create(0, gtype);
  h->index = arr_create(0, long);
  h->index2 = arr_create(0, long);
  h->cmp = cmp;
  return h;
}

void gtype_free_p2w(gtype value) {
  p2w_free(value.p2w);
}

void p2w_switch(struct p2ways *h, long e1, long e2) {
  if (e1 != e2) {
    long tmp1, tmp2;
    gtype_swap(h->data[e1], h->data[e2]);

    tmp1 = h->index[e1];
    tmp2 = h->index[e2];

    arr_set_value_with_index(h->index2, e2 + 2, tmp1);
    arr_set_value_with_index(h->index2, e1 + 2, tmp2);

    arr_set_value_with_index(h->index, tmp2, e1);
    arr_set_value_with_index(h->index, tmp1, e2);
  }
}

void p2w_shift_up(struct p2ways *h, long elem) {
  if (elem == 0 ||
      h->cmp(h->data[elem], h->data[HTOP(elem)]) < 0) {
    /* at the top */
  } else {
    p2w_switch(h, elem, HTOP(elem));
    p2w_shift_up(h, HTOP(elem));
  }
}

void p2w_sink(struct p2ways *h, long head) {
  long size = p2w_size(h);
  if (HLEFT(head) >= size) {
    /* no subtrees */
  } else if (HRIGHT(head) == size ||
         h->cmp(h->data[HLEFT(head)], h->data[HRIGHT(head)]) >= 0) {
    /* sink to the left if needed */
    if (h->cmp(h->data[head], h->data[HLEFT(head)]) < 0) {
      p2w_switch(h, head, HLEFT(head));
      p2w_sink(h, HLEFT(head));
    }
  } else {
    /* sink to the right */
    if (h->cmp(h->data[head], h->data[HRIGHT(head)]) < 0) {
      p2w_switch(h, head, HRIGHT(head));
      p2w_sink(h, HRIGHT(head));
    }
  }
}

int p2w_push_with_index(struct p2ways *h, long idx, gtype elem) {
  long size = arr_size(h->data);
  arr_append(h->data, elem);
  arr_append(h->index, idx);
  arr_set_value_with_index(h->index2, size + 2, idx);

  p2w_shift_up(h, size);
  return 0;
}

gtype p2w_max(const struct p2ways *h) {
  return h->data[0];
}

long p2w_max_index(const struct p2ways *h) {
  return h->index[0];
}

int p2w_has_elem(const struct p2ways *h, long idx) {
  return h->index2[idx] != 0;
}

int p2w_has_active(const struct p2ways *h, long idx) {
  return h->index2[idx] > 1;
}

gtype p2w_get(const struct p2ways *h, long idx) {
  long i = h->index2[idx] - 2;
  return h->data[i];
}

gtype p2w_delete_max(struct p2ways *h) {
  gtype tmp = h->data[0];
  long tmpidx = h->index[0];
  p2w_switch(h, 0, p2w_size(h) - 1);
  arr_resize(h->data, arr_size(h->data) - 1);
  arr_resize(h->index, arr_size(h->index) - 1);
  arr_set_value_with_index(h->index2, 0, tmpidx);
  p2w_sink(h, 0);

  return tmp;
}

gtype p2w_deactivate_max(struct p2ways *h) {
  gtype tmp = h->data[0];
  long tmpidx = h->index[0];
  p2w_switch(h, 0, p2w_size(h) - 1);
  arr_resize(h->data, arr_size(h->data) - 1);
  arr_resize(h->index, arr_size(h->index) - 1);
  arr_set_value_with_index(h->index2, 1, tmpidx);
  p2w_sink(h, 0);

  return tmp;
}

gtype p2w_delete_max_index(struct p2ways *h, long *idx) {
  gtype tmp = h->data[0];
  long tmpidx = h->index[0];
  p2w_switch(h, 0, p2w_size(h) - 1);
  arr_resize(h->data, arr_size(h->data) - 1);
  arr_resize(h->index, arr_size(h->index) - 1);
  arr_set_value_with_index(h->index2, 0, tmpidx);
  p2w_sink(h, 0);

  if (idx) {
    *idx = tmpidx;
  }
  return tmp;
}

int p2w_modify(struct p2ways *h, long idx, gtype elem) {
  long pos = h->index2[idx] - 2;

  h->data[pos] = elem;
  p2w_sink(h, pos);
  p2w_shift_up(h, pos);

  return 0;
}

int p2w_check(struct p2ways *h) {
  long size = p2w_size(h);
  int ecode = 0;
  for (long i = 0; i < size; i++) {
    if (HLEFT(i) >= size) {
      break;
    }
    if (h->cmp(h->data[HLEFT(i)], h->data[i]) > 0) {
      ecode = 1;
      break;
    }
    if (HRIGHT(i) >= size) {
      break;
    }
    if (h->cmp(h->data[HRIGHT(i)], h->data[i]) > 0) {
      ecode = 1;
      break;
    }
  }

  return ecode == 0;
}

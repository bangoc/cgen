/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef GTP2WHEAP_H_
#define GTP2WHEAP_H_

#include "gtvector.h"
#include "ivector.h"

#include <stdbool.h>

typedef struct p2wheap {
    size_t size;
    vector_t data;
    vector_t index;
    vector_t index2;
} *p2wheap_t;

#define PARENT(x)   (((x)+1)/2-1)
#define LEFTCHILD(x)  (((x)+1)*2-1)
#define RIGHTCHILD(x) (((x)+1)*2)

// ========== Khai báo hàm ===============

static p2wheap_t p2w_create();
static void p2w_free(p2wheap_t *h);
static size_t p2w_size(const p2wheap_t h);
static int p2w_clear(p2wheap_t h);
static bool p2w_empty(const p2wheap_t h);
static int p2w_push_with_index(p2wheap_t h, long idx, gtype elem, gtype_cmp_t cmp);
static gtype p2w_max(const p2wheap_t h);
static long p2w_max_index(const p2wheap_t h);
static gtype p2w_get(const p2wheap_t h, long idx);
static gtype p2w_delete_max(p2wheap_t h, gtype_cmp_t cmp);
static gtype p2w_deactivate_max(p2wheap_t h, gtype_cmp_t cmp);
static gtype p2w_delete_max_index(p2wheap_t h, long *idx, gtype_cmp_t cmp);
static int p2w_modify(p2wheap_t h, long idx, gtype elem, gtype_cmp_t cmp);


// ========== Macro viết nhanh ===========


// ========== Định nghĩa hàm =============

static int p2w_init(p2wheap_t h) {
  h->size = 0;
  h->data = gtv_create();
  h->index = gtv_create();
  h->index2 = gtv_create();

  return 0;
}

static p2wheap_t p2w_create() {
  p2wheap_t h = malloc(sizeof(struct p2wheap));
  p2w_init(h);
  return h;
}

static void p2w_free(p2wheap_t *h) {
  gtv_free(&(*h)->data);
  gtv_free(&(*h)->index);
  gtv_free(&(*h)->index2);
  free(*h);
  *h = NULL;
}

static size_t p2w_size(const p2wheap_t h) {
  return gtv_size(h->data);
}

static void p2w_switch(p2wheap_t h, long e1, long e2) {
  if (e1 != e2) {
    long tmp1, tmp2;
    gtype tmp3 = h->data[e1];
    h->data[e1] = h->data[e2];
    h->data[e2] = tmp3;

    tmp1 = h->index[e1].i;
    tmp2 = h->index[e2].i;

    gtv_set_value_with_index(&h->index2, gtype_value(i, e2 + 2), tmp1);
    gtv_set_value_with_index(&h->index2, gtype_value(i, e1 + 2), tmp2);

    gtv_set_value_with_index(&h->index, gtype_value(i, tmp2), e1);
    gtv_set_value_with_index(&h->index, gtype_value(i, tmp1), e2);
  }
}

static void p2w_shift_up(p2wheap_t h, long elem, gtype_cmp_t cmp) {
  if (elem == 0 || cmp(h->data[elem], h->data[PARENT(elem)]) < 0) {
    /* at the top */
  } else {
    p2w_switch(h, elem, PARENT(elem));
    p2w_shift_up(h, PARENT(elem), cmp);
  }
}

static void p2w_sink(p2wheap_t h, long head, gtype_cmp_t cmp) {
  size_t size = p2w_size(h);
  if (LEFTCHILD(head) >= size) {
    /* no subtrees */
  } else if (RIGHTCHILD(head) == size ||
         cmp(h->data[LEFTCHILD(head)], h->data[RIGHTCHILD(head)]) >= 0) {
    /* sink to the left if needed */
    if (cmp(h->data[head], h->data[LEFTCHILD(head)]) < 0) {
      p2w_switch(h, head, LEFTCHILD(head));
      p2w_sink(h, LEFTCHILD(head), cmp);
    }
  } else {
    /* sink to the right */
    if (cmp(h->data[head], h->data[RIGHTCHILD(head)]) < 0) {
      p2w_switch(h, head, RIGHTCHILD(head));
      p2w_sink(h, RIGHTCHILD(head), cmp);
    }
  }
}

static int p2w_clear(p2wheap_t h) {
  gtv_setsize(h->data, 0);
  gtv_setsize(h->index, 0);
  gtv_setsize(h->index2, 0);
  return 0;
}

static bool p2w_empty(const p2wheap_t h) {
  return gtv_size(h->data) == 0;
}

static int p2w_push_with_index(p2wheap_t h, long idx, gtype elem, gtype_cmp_t cmp) {
  size_t size = gtv_size(h->data);
  gtv_push_back(&h->data, elem);
  ivec_push_back(&h->index, idx);
  gtv_set_value_with_index(&h->index2, gtype_value(i, size + 2), idx);

  p2w_shift_up(h, size, cmp);
  return 0;
}

static size_t p2w_max_size(const p2wheap_t h) {
  return h->size;
}

static gtype p2w_max(const p2wheap_t h) {
  return h->data[0];
}

static long p2w_max_index(const p2wheap_t h) {
  return h->index[0].i;
}

static bool p2w_has_elem(const p2wheap_t h, long idx) {
  return h->index2[idx].i != 0;
}

static bool p2w_has_active(const p2wheap_t h, long idx) {
  return h->index2[idx].i > 1;
}

static gtype p2w_get(const p2wheap_t h, long idx) {
  long i = h->index2[idx].i - 2;
  return h->data[i];
}

static gtype p2w_delete_max(p2wheap_t h, gtype_cmp_t cmp) {
  gtype tmp = h->data[0];
  long tmpidx = h->index[0].i;
  p2w_switch(h, 0, p2w_size(h) - 1);
  gtv_setsize(h->data, gtv_size(h->data) - 1);
  gtv_setsize(h->index, gtv_size(h->index) - 1);
  gtv_set_value_with_index(&h->index2, gtype_value(i, 0), tmpidx);
  p2w_sink(h, 0, cmp);

  return tmp;
}

static gtype p2w_deactivate_max(p2wheap_t h, gtype_cmp_t cmp) {
  gtype tmp = h->data[0];
  long tmpidx = h->index[0].i;
  p2w_switch(h, 0, p2w_size(h) - 1);
  gtv_setsize(h->data, gtv_size(h->data) - 1);
  gtv_setsize(h->index, gtv_size(h->index) - 1);
  gtv_set_value_with_index(&h->index2, gtype_value(i, 1), tmpidx);
  p2w_sink(h, 0, cmp);

  return tmp;
}

static gtype p2w_delete_max_index(p2wheap_t h, long *idx, gtype_cmp_t cmp) {
  gtype tmp = h->data[0];
  long tmpidx = h->index[0].i;
  p2w_switch(h, 0, p2w_size(h) - 1);
  gtv_setsize(h->data, gtv_size(h->data) - 1);
  gtv_setsize(h->index, gtv_size(h->index) - 1);
  gtv_set_value_with_index(&h->index2, gtype_value(i, 0), tmpidx);
  p2w_sink(h, 0, cmp);

  if (idx) {
    *idx = tmpidx;
  }
  return tmp;
}

static int p2w_modify(p2wheap_t h, long idx, gtype elem, gtype_cmp_t cmp) {
  long pos = h->index2[idx].i - 2;

  h->data[pos] = elem;
  p2w_sink(h, pos, cmp);
  p2w_shift_up(h, pos, cmp);

  return 0;
}

static bool p2w_check(p2wheap_t h, gtype_cmp_t cmp) {
  size_t size = p2w_size(h);
  int ecode = 0;
  for (long i = 0; i < size; i++) {
    if (LEFTCHILD(i) >= size) {
      break;
    }
    if (cmp(h->data[LEFTCHILD(i)], h->data[i]) > 0) {
      ecode = 1;
      break;
    }
    if (RIGHTCHILD(i) >= size) {
      break;
    }
    if (cmp(h->data[RIGHTCHILD(i)], h->data[i]) > 0) {
      ecode = 1;
      break;
    }
  }

  return ecode == 0;
}


#endif  // GTP2WHEAP_H_
#include "all.h"

#include "tests/base/utils.h"

#include <stdlib.h>

int qsort_cmp_l(const void *v1, const void *v2) {
  return gtype_cmp_l(*((const gtype*)v1), *((const gtype*)v2));
}

int t1(int n) {
  struct gvector *v = gvec_create(n, NULL);
  for (int i = 0; i < n; ++i) {
    gvec_elem(v, i).l = rand() % n;
  }
  struct gvector *vsel = gvec_clone(v);
  struct gvector *vins = gvec_clone(v);
  struct gvector *vbub = gvec_clone(v);
  struct gvector *vq2 = gvec_clone(v);
  struct gvector *vq2m3 = gvec_clone(v);
  struct gvector *vq3 = gvec_clone(v);
  struct gvector *vquick = gvec_clone(v);
  struct gvector *vqsort = gvec_clone(v);
  struct gvector *vqins = gvec_clone (v);
  struct gvector *vheap = gvec_clone (v);
  selsort(gvec_size(vsel), gvec_arr(vsel), gtype_cmp_l);
  insort(gvec_size(vins), gvec_arr(vins), gtype_cmp_l);
  bubsort(gvec_size(vbub), gvec_arr(vbub), gtype_cmp_l);
  q2sort(gvec_size(vq2), gvec_arr(vq2), gtype_cmp_l);
  q2m3sort(gvec_size(vq2m3), gvec_arr(vq2m3), gtype_cmp_l);
  q3sort(gvec_size(vq3), gvec_arr(vq3), gtype_cmp_l);
  quicksort(gvec_size(vquick), gvec_arr(vquick), gtype_cmp_l);
  qinsort(gvec_size(vqins), gvec_arr(vqins), gtype_cmp_l);
  heapsort(gvec_size(vheap), gvec_arr(vheap), gtype_cmp_l);
  qsort(gvec_arr(vqsort), gvec_size(vqsort), sizeof(gtype), qsort_cmp_l);
  CHECK_MSG(gvec_identical(vsel, vins), "Selection & Insertion");
  CHECK_MSG(gvec_identical(vsel, vbub), "Selection & Bubble");
  CHECK_MSG(gvec_identical(vsel, vq2), "Selection & Quick 2 ways partition");
  CHECK_MSG(gvec_identical(vsel, vq2m3), "Selection & Quick 2 ways partition, median of low, mid, high");
  CHECK_MSG(gvec_identical(vsel, vq3), "Selection & Quick 3 ways partition");
  CHECK_MSG(gvec_identical(vsel, vquick), "Selection & Quick sort");
  CHECK_MSG(gvec_identical(vsel, vqsort), "Selection & stdlib.h qsort");
  CHECK_MSG(gvec_identical(vsel, vqins), "Selection & Mix of q2me and ins");
  CHECK_MSG(gvec_identical(vsel, vheap), "Selection & Mix of q2me and ins");
  gvec_free(v);
  gvec_free(vsel);
  gvec_free(vins);
  gvec_free(vbub);
  gvec_free(vq2);
  gvec_free(vq2m3);
  gvec_free(vq3);
  gvec_free(vquick);
  gvec_free(vqsort);
  gvec_free(vqins);
  gvec_free(vheap);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog 10000\n");
    return 1;
  }
  int n;
  srand(time(NULL));
  sscanf(argv[1], "%d", &n);
  CHECK_MSG(t1(n) == 0, "t1");
  TEST_OK();
  return 0;
}
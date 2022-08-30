#include "base/core.h"
#include "base/rb.h"

#include <stdio.h>

#define MIN 100000l
#define POINTS 10l

int usage() {
  printf("./Usage: ./p 10000000\nTham số phải > %ld và chia hết cho %ld.\n", MIN, POINTS);
  return 1;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return usage();
  }
  long n = MIN;
  sscanf(argv[1], "%ld", &n);
  if (n < MIN || n % 10 != 0) {
    return usage();
  }
  const long len = n / POINTS;
  char desc[1024];
  long value = 0;
  bs_tree_t t = bs_create_tree(NULL, gtype_cmp_l, NULL);
  for (long point = 0; point < POINTS; ++point) {
    sprintf(desc, "%ld x insert from %ld (s): ", len, len * point);
    BENCH(desc, 1,
            for (long i = 0; i < len; ++i) {
              rb_insert(t, gtype_l(value++));
            }
          );
    sprintf(desc, "%ld x search from %ld (s): ", len, len * point);
    BENCH(desc, 1,
            for (long i = 0; i < len; ++i) {
              bs_search(t, gtype_l(len * point + i));
            }
          );
  }

  // xóa
  value = 0;
  for  (long point = 0; point < POINTS; ++point) {
    sprintf(desc, "%ld x delete from %ld (s): ", len, n - len * point);
    BENCH(desc, 1,
            bs_node_t tmp;
            for (long i = 0; i < len; ++i) {
              tmp = bs_search(t, gtype_l(value++));
              if (tmp) {
                rb_delete(t, tmp);
                free(tmp);
              }
            }
          );
  }
  bs_free_tree(t);
  return 0;
}
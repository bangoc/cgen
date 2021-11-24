#include "core.h"
#include "tests/rb/rbi.h"

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
  long n;
  sscanf(argv[1], "%ld", &n);
  if (n <= MIN || n % 10 != 0) {
    return usage();
  }
  const long len = n / POINTS;
  char desc[1024];
  long value = 0;
  bn_tree_t t = bn_create_tree(NULL_PTR);
  for (long point = 0; point < POINTS; ++point) {
    sprintf(desc, "%ld x insert from %ld (s): ", len, len * point);
    BENCH(desc, 1,
            for (long i = 0; i < len; ++i) {
              rbi_insert(t, value++);
            }
          );
    sprintf(desc, "%ld x search from %ld (s): ", len, len * point);
    BENCH(desc, 1,
            for (long i = 0; i < len; ++i) {
              rbi_search(t, len * point + i);
            }
          );
  }

  // xóa
  value = 0;
  for  (long point = 0; point < POINTS; ++point) {
    sprintf(desc, "%ld x delete from %ld (s): ", len, n - len * point);
    BENCH(desc, 1,
            for (long i = 0; i < len; ++i) {
              rbi_delete(t, value++);
            }
          );
  }
  return 0;
}
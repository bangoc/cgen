#include "all.h"
#include "tests/ut/helpers.h"
#include "tests/ut/utils.h"

#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("usage: ./p #Ops max_value\nExample: ./p 10000 1000\n");
    return 1;
  }
  long num_ops, max_value;
  sscanf(argv[1], "%ld", &num_ops);
  sscanf(argv[2], "%ld", &max_value);
  srand(time(NULL));
  struct tmap *t = tcreate(glong_cmp);
  for (long i = 0; i < num_ops; ++i) {
    int op = rand() % 2;
    int value = rand() % max_value + 1;
    if (op == 0) {
      // insert
      tinsert(t, GLONG(value), GLONG(0));
    } else {
      // delete
      tremove(t, GLONG(value));
    }

    // Kiểm tra sau từng thao tác
    CHECK_MSG(rb_is_valid(t), "Không phải cây đỏ-đen");
  }
  printf("%ld thao tác Ok\n", num_ops);
  tfree(t);
  TEST_OK();
}
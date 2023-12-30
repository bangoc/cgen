#include "all.h"
#include "tests/helpers.h"
#include "tests/utils.h"

#include <stdlib.h>
#include <time.h>

TDECL_IMPL(iimap, int, int, ii)
RB_DECL_IMPL(iimap, TNN(iimap))

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./p #Ops max_value\nExample: ./p 10000 1000\n");
    return 1;
  }
  long num_ops, max_value;
  sscanf(argv[1], "%ld", &num_ops);
  sscanf(argv[2], "%ld", &max_value);
  srand(time(NULL));
  struct iimap *t = iimap(cmpi);
  for (long i = 0; i < num_ops; ++i) {
    int op = rand() % 2;
    int value = rand() % max_value + 1;
    if (op == 0) {
      // insert
      iiput(t, value, 1);
    } else {
      // delete
      iiremove(t, value);
    }

    // Kiểm tra sau từng thao tác
    CHECK_MSG(rb_is_valid(t), "Không phải cây đỏ-đen");
  }
  printf("%ld thao tác Ok\n", num_ops);
  while (t->size) {
    iidelete(t, t->root);
  }
  iifree(t);
  TEST_OK();
}
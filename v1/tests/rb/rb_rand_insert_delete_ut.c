#include "rbi.h"
#include "tests/base/helpers.h"
#include "tests/base/utils.h"

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
  struct grbtree *t = rbi_create_tree(NULL);
  for (long i = 0; i < num_ops; ++i) {
    int op = rand() % 2;
    int value = rand() % max_value + 1;
    if (op == 0) {
      // insert
      rbi_insert(t, value);
    } else {
      // delete
      rbi_delete(t, value);
    }

    // Kiểm tra sau từng thao tác
    CHECK_MSG(rb_is_valid(t), "Không phải cây đỏ-đen");
  }
  printf("%ld thao tác Ok\n", num_ops);
  rbi_free_tree(t);
  return 0;
}
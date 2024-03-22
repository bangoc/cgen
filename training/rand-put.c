#include "bst-int.h"

struct bst_node {
  int key;
  struct bst_node *left;
  struct bst_node *right;
  struct bst_node *top;
};

struct bst_tree {
  struct bst_node *root;
  int size;
};

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_key(int n) {
  return rand() % (2 * n) + 1;
}

#define TCOUNT 5

struct test_data {
  struct bst_tree *cases[TCOUNT];
};

int new_key;
int asw;

struct test_data *rand_test(int n) {
  struct test_data *test = malloc(sizeof(struct test_data));
  for (int i = 0; i < TCOUNT; ++i) {
    test->cases[i] = bst_tree();
  }
  for (int i = 0; i < n; ++i) {
    int key = rand_key(n);
    for (int j = 0; j < TCOUNT; ++j) {
      bst_put(test->cases[j], key);
    }
  }
  new_key = rand_key(n);
  asw = rand() % (TCOUNT - 1) + 1;
  bst_put(test->cases[asw], new_key);
  for (int i = 1; i < TCOUNT; ++i) {
    if (i == asw) {
      continue;
    }
    int nok;
    do {
      struct bst_tree *t = test->cases[i];
      struct bst_node *p = t->root, *c;
      int r = 0;
      for (;;) {
        r = rand() % 2;
        c = r? p->right: p->left;
        if (!c) {
          break;
        }
        p = c;
      }
      struct bst_node **loc = r? &p->right: &p->left;
      *loc = bst_node(new_key);
      (*loc)->top = p;
      ++t->size;
      nok = bst_equal(t, test->cases[asw]);
      for (int j = 1; j < i; ++j) {
        nok = nok || bst_equal(t, test->cases[j]);
      }
      if (nok) {
        free(*loc);
        *loc = NULL;
        --t->size;
      }
    } while (nok);
  }
  return test;
}

char *msg[] = {"Trúng phóc", "Tuyệt vời", "Xuất sắc", "Rất tốt"};
const int msg_count = sizeof(msg)/sizeof(msg[0]);

int do_test() {
  int n = 5;
  struct test_data *test = rand_test(n);
  printf("Cho t là cây nhị phân tìm kiếm đang ở trạng thái như trong hình\n");
  bst_pprint(test->cases[0]);
  printf("Hãy cho biết cây nhị phân tìm kiếm thu được sau khi thực hiện lệnh bst_put(t, %d)?\n", new_key);
  for (int i = 1; i < TCOUNT; ++i) {
    printf("--------------------- Đáp án %d -----------------\n", i);
    bst_pprint(test->cases[i]);
  }
  printf("Lựa chọn của bạn là: ");
  int choice;
  scanf("%d", &choice);
  if (choice == asw) {
    printf("%s\n", msg[rand() % msg_count]);
  } else {
    printf("Sai rồi, đáp án đúng là %d\n", asw);
  }
  for (int i = 0; i < TCOUNT; ++i) {
    bst_free(test->cases[i]);
  }
  free(test);
  return choice == asw;
}

int main() {
  srand(time(NULL));
  const int test_num = 3;
  int total = 0;
  for (int i = 0; i < test_num; ++i) {
    printf("[Lượt %d/%d] ", i + 1, test_num);
    total += do_test();
  }
  printf("Số lượng câu trả lời đúng là %d/%d  ==> ", total, test_num);
  if (total == test_num) {
    printf("Chúc mừng vì đã vượt qua bài kiểm tra!\n");
  } else {
    printf("Chưa đạt, hãy cố gắng hơn trong lần sau nhé!\n");
  }
}
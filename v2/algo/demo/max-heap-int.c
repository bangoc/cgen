#include <stdio.h>

#define HLEFT(i) (((i) << 1) + 1)
#define HRIGHT(i) (((i) << 1) + 2)
#define SWAP(a, b) { int _tmp = (a); (a) = (b); (b) = _tmp; }

void heap_shift_down(long i, long n, int *a) {
  for (;;) {
    long lc = HLEFT(i), rc = HRIGHT(i), root = i;
    if (lc < n && a[root] < a[lc]) {
      root = lc;
    }
    if (rc < n && a[root] < a[rc]) {
      root = rc;
    }
    if (root == i) {
      break;
    }
    SWAP(a[i], a[root]);
    i = root;
  }
}
void heap_make(long n, int *a) {
  for (long i = n / 2; i >= 0; --i) {
    heap_shift_down(i, n, a);
  }
}
int main() {
  int a[] = {3, 1, 2, 9, 20, 18, 29, 22, 11, 15, 21};
  int n = sizeof(a)/sizeof(a[0]);
  heap_make(n, a);
  printf("Nhập k = ");
  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; ++i) {
    printf("%d\n", a[0]);
    SWAP(a[0], a[n - i - 1]);
    heap_shift_down(0, n - i - 1, a);
  }
}
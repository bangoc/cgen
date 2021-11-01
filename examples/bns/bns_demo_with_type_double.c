/*
  (C) Nguyen Ba Ngoc 2021
  Trong ví dụ này chương trình sẽ hỏi người dùng nhập vào các số thực
  cho tới khi người dùng nhập vào 1 số âm.
  Các số không âm được thêm vào một cây nhị phân tìm kiếm, sau đó
  được xuất ra theo thứ tự tăng dần và thứ tự giảm dần.
*/

#include "cgen.ic"

int main() {
  bn_tree_t t = bns_create_tree_g(NULL, gtype_cmp_d);
  double val;
  printf("Nhập vào một dãy số thực không âm (nhập 1 số âm bất kỳ để kết thúc nhập): \n");
  for (;;) {
    scanf("%lf", &val);
    if (val < 0) {
      break;
    }
    bns_insert_g(t, gtype_d(val));
  }
  long sz = bn_size(t);
  printf("Số lượng số không âm đã nhập: %ld\n", sz);
  if (sz > 0) {
    bns_pprint(t, gtype_print_d);
    printf("Các số theo thứ tự tăng dần: ");
    bn_traverse_lnr(cur, t) {
      printf(" %f", bns_node_g_key(cur).d);
    }
    printf("\nCác số theo thứ tự giảm dần: ");
    bn_traverse_rnl(cur, t) {
      printf(" %f", bns_node_g_key(cur).d);
    }
    printf("\n");
  }
  bn_free_tree(&t);
  return 0;
}
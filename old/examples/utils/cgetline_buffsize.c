/* (C) Nguyen Ba Ngoc */

/**
 * Minh họa sử dụng cgetline
 */

#include "utils/io.h"

#include <string.h>

int main() {
  char *line = NULL;
  long n = 0;
  printf("Nhập vào 1 dòng (nhập STOP để kết thúc chương trình): ");
  for (;;) {
    // Có thể sử dụng NULL hoặc 0 thay cho &n nếu không quan tâm đến
    // kích thước vùng nhớ được cập phát
    cgetline(&line, &n, stdin);
    if (strcmp(line, "STOP\n") == 0) {
      break;
    }
    printf("Dòng đã nhập: %s", line);
    printf("Độ dài chuỗi ký tự: %zu\n", strlen(line));
    printf("Kích thước vùng nhớ: %ld\n", n);
  }
  free(line);
  return 0;
}
#ifndef EXT_IO_H_
#define EXT_IO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Hàm cgetline đọc 1 dòng từ luồng nhập dữ liệu văn bản inp
 * (ví dụ tệp văn bản). Hàm đọc dữ liệu cho tới khi gặp ký tự
 * LF ('\n') hoặc kết thúc tệp, tự cấp phát hoặc cấp phát lại bộ
 * nhớ đủ để lưu dữ liệu đọc được.
 *
 * Các tham số:
 *    lineptr: con trỏ chuỗi ký tự lưu kết quả đọc dữ liệu
 *             (được phép NULL).
 *    n: là kích thước vùng nhớ đã được cấp phát cho *lineptr
 *       (nếu chưa cấp phát thì n == 0).
 *    inp: con trỏ tới luồng nhập văn bản.
 *
 *    Nếu *lineptr == NULL thì n == 0 và ngược lại, hàm sẽ tự
 *    cấp phát bộ nhớ động trong trường hợp này. Người sử dụng
 *    tự giải phóng bộ nhớ sau khi sử dụng.
 *
 * Giá trị trả về:
 *    Trả về chuỗi ký tự lưu dòng đọc được. Trong trường hợp
 *    không thể đọc được dữ liệu từ inp (ví dụ kết thúc tệp)
 *    hàm trả về NULL và giá trị *lineptr không thay đổi.
 *    Trong trường hợp không thể cấp phát được bộ nhớ để lưu
 *    dòng, hàm trả về NULL và *lineptr == NULL.
 */
static char *cgetline(char **lineptr, long n, FILE *inp) {
#ifndef CGETLINE_BUFF_SIZE
  #define CGETLINE_BUFF_SIZE 1024
#endif  // CGETLINE_BUFF_SIZE

  static char buff[CGETLINE_BUFF_SIZE];
  long idx = 0, len, tmp;

  while (fgets(buff, CGETLINE_BUFF_SIZE, inp)) {
    len = strlen(buff);
    tmp = idx + len + 1;
    if (tmp > n) {
      *lineptr = realloc(*lineptr, tmp);
      if (*lineptr) {
        n = tmp;
      } else {
        return NULL;  // Lỗi cấp phát bộ nhớ
      }
    }
    if (idx == 0) {
      *lineptr[0] = 0;
    }
    strcat(*lineptr, buff);
    idx += len;
    if (buff[len - 1] == '\n') {
      break;
    }
  }
  return idx > 0? *lineptr: NULL;
#undef CGETLINE_BUFF_SIZE
}

static void clear_stdin() {
  while (getchar() != '\n');
}

static void remove_tail_lf(char *s) {
  if (!s) {
    return;
  }
  char *p = s + strlen(s) - 1;
  if (*p == '\n') {
    *p = '\0';
  }
}

#endif  // EXT_IO_H_
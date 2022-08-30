#ifndef UTILS_IO_H_
#define UTILS_IO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CGEN_IO_BUF_SIZE
  #define CGEN_DEFAULT_IO_BUFF_SIZE
  #define CGEN_IO_BUF_SIZE 1024
#endif  // CGEN_IO_BUF_SIZE

/*
 * Hàm cgetline đọc 1 dòng từ luồng nhập dữ liệu văn bản inp
 * (ví dụ tệp văn bản). Hàm đọc dữ liệu cho tới khi gặp ký tự
 * LF ('\n') hoặc kết thúc tệp, tự cấp phát hoặc cấp phát lại bộ
 * nhớ đủ để lưu dữ liệu đọc được.
 *
 * Các tham số:
 *    lineptr: con trỏ tới vùng nhớ lưu kết quả đọc dữ liệu
 *             (được phép NULL).
 *    n: là kích thước vùng nhớ đã được cấp phát cho *lineptr
 *       (nếu chưa cấp phát thì n == 0).
 *    inp: con trỏ tới luồng nhập văn bản.
 *
 *    Nếu *lineptr == NULL thì n == 0 và ngược lại, hàm sẽ tự
 *    cấp phát bộ nhớ động trong trường hợp này. Người sử dụng
 *    tự giải phóng bộ nhớ sau khi sử dụng.
 *    Nếu *lineptr != NULL thì *ptr phải trỏ vào vùng nhớ đã
 *    được cấp phát, và n là kích thước vùng nhớ đã được cấp phát
 *    cho *lineptr
 *
 * Giá trị trả về:
 *    Trả về chuỗi ký tự lưu dòng đọc được (*lineptr). Trong trường
 *    hợp không thể đọc được dữ liệu từ inp (ví dụ kết thúc tệp)
 *    hàm trả về NULL và giá trị *lineptr không thay đổi.
 *    Trong trường hợp không thể cấp phát được bộ nhớ để lưu
 *    dòng, hàm trả về NULL và *lineptr == NULL.
 */
static char *cgetline(char **lineptr, long *nptr, FILE *inp) {
  char buff[CGEN_IO_BUF_SIZE];
  long idx = 0, len, tmp;
  long n = nptr? *nptr: 0;
  while (fgets(buff, CGEN_IO_BUF_SIZE, inp)) {
    len = strlen(buff);
    tmp = idx + len + 1;
    if (tmp > n) {
      *lineptr = realloc(*lineptr, tmp);
      if (*lineptr == NULL) {
        return NULL;  // Lỗi cấp phát bộ nhớ
      }
      n = tmp;
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
  if (idx == 0) {
    return NULL;
  }
  if (nptr) {
    *nptr = n;
  }
  return *lineptr;
}

#define clear_stdin() while (getchar() != '\n')

static char *remove_tail_lf(char *s) {
  if (!s) {
    return s;
  }
  char *p = s + strlen(s) - 1;
  if (*p == '\n') {
    *p = '\0';
  }
  return s;
}

#ifdef CGEN_DEFAULT_IO_BUFF_SIZE
  #undef CGEN_IO_BUF_SIZE
#endif  // CGEN_DEFAULT_IO_BUFF_SIZE

#endif  // UTILS_IO_H_

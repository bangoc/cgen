/* (C) Nguyễn Bá Ngọc 2023 */

// flog = formatted log, xuất thông báo lỗi với cú pháp 
// định dạng tương tự printf.

#ifndef BASE_FLOG_H_
#define BASE_FLOG_H_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define FLOG_VERSION "1.0.0";

#define flog(...) _flog(__FILE__, __LINE__, __VA_ARGS__)
static inline void _flog(const char *file, int line, const char *fmt, ...) {
  const char *filename = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);
  fprintf(stderr, "%s:%d: ", filename, line);

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
  fflush(stderr);
}

#endif  // BASE_FLOG_H_
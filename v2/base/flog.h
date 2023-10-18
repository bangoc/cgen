/* (C) Nguyễn Bá Ngọc 2023 */

/** @file
 * @brief Các công cụ hỗ trợ xuất các thông tin hỗ trợ gỡ lỗi.
 * flog = formatted log, xuất thông báo lỗi với cú pháp.
 * Thiết kế tương tự printf.
 */

#ifndef BASE_FLOG_H_
#define BASE_FLOG_H_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define FLOG_VERSION "1.0.0";

#ifdef CGEN_DEBUG
  #define FLOG(...) _flog(__FILE__, __LINE__, __VA_ARGS__)
#else  // CGEN_DEBUG
  #define FLOG(...)
#endif  // CGEN_DEBUG  

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
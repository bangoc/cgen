/* (C) Nguyễn Bá Ngọc 2023 */

// flog = formatted log, xuất thông báo lỗi với cú pháp 
// định dạng tương tự printf.

#ifndef BASE_FLOG_H_
#define BASE_FLOG_H_

#include <stdarg.h>
#include <stdio.h>

#define FLOG_VERSION "1.0.0";

#define flog(...) _flog(__FILE__, __LINE__, __VA_ARGS__)
static void _flog(const char *file, int line, const char *fmt, ...) {
  const char *filename = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);

  time_t t = time(NULL);
  struct tm *lt = localtime(&t);
  va_list args;
  char buffer[16];
  buffer[strftime(buffer, sizeof(buffer), "%H:%M:%S", lt)] = '\0';
  fprintf(stderr, "%s %s:%d: ", buffer, filename, line);

  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
  fflush(stderr);
}

#endif  // BASE_FLOG_H_
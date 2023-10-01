/* (C) Nguyễn Bá Ngọc 2023 */

// flog = formatted log, xuất thông báo lỗi với cú pháp 
// định dạng tương tự printf.

#ifndef BASE_FLOG_H_
#define BASE_FLOG_H_

#include <stdarg.h>
#include <stdio.h>

#define FLOG_VERSION "1.0.0";

static const char *flog_names[] = 
    {"ALL", "TRACE", "DEBUG", "INFO", "WARNING", "ERROR", "NONE"};

enum flog_levels { ALL, TRACE, DEBUG, INFO, WARNING, ERROR, NONE };

#define flog(LEVEL, ...) _flog(LEVEL, __FILE__, __LINE__, __VA_ARGS__)
static void _flog(int level, 
      const char *file, int line, const char *fmt, ...) {

  if (level < TRACE || level > ERROR) {
    flog(ERROR, "%s", "Gọi flog với LEVEL không hợp lệ.");
    return;
  }

  const char *filename = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);

  time_t t = time(NULL);
  struct tm *lt = localtime(&t);
  va_list args;
  char buffer[16];
  buffer[strftime(buffer, sizeof(buffer), "%H:%M:%S", lt)] = '\0';
  fprintf(stderr, "%s %-8s %s:%d: ", buffer, flog_names[level],
          filename, line);

  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
  fflush(stderr);
}

#endif  // BASE_FLOG_H_
#ifndef UTILS_STR_H_
#define UTILS_STR_H_

/* (C) Nguyen Ba Ngoc 2022 */

#include "vec/gvec.h"

extern const char* ascii_spaces;

struct gvector *str_tokens(char *line, const char *delims);

#define str_split(line) str_tokens(line, ascii_spaces)
#define tok_traverse(cur, line, delims) \
  for (char *cur = strtok(line, delims); cur; cur = strtok(NULL, delims))

/*
  Trả về bản sao của chuỗi s hoặc NULL nếu không thể
  cấp phát bộ nhớ.
  Ghi chú: strdup là một hàm trong mở rộng, không có
  trong thư viện tiêu chuẩn.
*/
static inline char * cstrdup (const char *s) {
  size_t len = strlen (s) + 1;
  void *snew = malloc (len);

  if (snew == NULL) {
    return NULL;
  }

  return (char *) memcpy (snew, s, len);
}

#endif  // UTILS_STR_H_
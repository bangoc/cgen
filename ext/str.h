#ifndef STR_H_
#define STR_H_

#include <stdlib.h>
#include <string.h>

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

#endif  // STR_H_
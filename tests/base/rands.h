/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Hỗ trợ sinh dữ liệu ngẫu nhiên.
*/

#ifndef TESTS_BASE_RANDS_H_
#define TESTS_BASE_RANDS_H_

#include <stdlib.h>

static char *rands(int n) {
  static char buff[21];
  if (n > 20) {
    n = 20;
  }
  for (int i = 0; i < n; ++i) {
    buff[i] = rand() % ('z' - 'a') + 'a';
  }
  buff[n] = '\0';
  return buff;
}

#endif  // TESTS_BASE_RANDS_H_
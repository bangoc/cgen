#ifndef TESTS_BASE_UTILS_H_
#define TESTS_BASE_UTILS_H_

#include <stdio.h>
#include <stdbool.h>

#define CHECK(op) if (!(op)) { return 1; }
#define CHECK_MSG(op, msg) do { \
    if (!(op)) { \
      printf("%s (%s:%d)\n", msg, __FILE__, __LINE__); \
      return 1; \
    } \
  } while (0)

#define CHECK_ECHO(op) CHECK_MSG(op, #op)

#define DEBUG_MSG(msg) printf("%s (%s:%d)\n", msg, __FILE__, __LINE__);

#define TEST_OK() \
    printf("Test Ok!\n"); \

#endif  // TESTS_BASE_UTILS_H_
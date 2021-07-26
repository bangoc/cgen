#ifndef TESTS_BASE_UTILS_H_
#define TESTS_BASE_UTILS_H_

#include <stdio.h>
#include <stdbool.h>

#define CHECK(op) if (!(op)) { return 1; }
#define CHECK_MSG(op, msg) if (!(op)) { printf("%s (%s:%d)\n", msg, __FILE__, __LINE__); return 1; }

#endif  // TESTS_BASE_UTILS_H_
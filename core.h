/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef CORE_H_
#define CORE_H_

#include <stddef.h>

#define container_of(ptr, type, member) \
  ((type *)((void*)ptr - offsetof(type, member)))

#endif  // CORE_H_
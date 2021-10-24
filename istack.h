#ifndef ISTACK_H_
#define ISTACK_H_

#include "gtlist1.h"

list1_t istk_push(list1_t list, long value);
long istk_pop(list1_t list);
long istk_top(list1_t list);

#endif  // ISTACK_H_
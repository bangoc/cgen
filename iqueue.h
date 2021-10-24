#ifndef IQUEUE_H_
#define IQUEUE_H_

#include "gtlist1.h"

list1_t iqu_enqueue(list1_t list, long value);
long iqu_dequeue(list1_t list);
long iqu_peek(list1_t list);

#endif  // IQUEUE_H_
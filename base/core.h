/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef BASE_CORE_H_
#define BASE_CORE_H_

#include <stddef.h>
#include <time.h>

#define container_of(ptr, type, member) \
  ((type *)((void*)ptr - offsetof(type, member)))

#define New(TYPE, ...) TYPE ## _create(  __VA_ARGS__ )

#define Delete(TYPE, ptr) do        \
        {       \
          TYPE ## _free(ptr); \
          /*free(ptr);*/    \
        }       \
        while(0)

#define BENCH(NAME, ITER, ...)    do { \
        double _sum = 0, _start, _stop; \
        for (int i = 0; i < ITER; ++i) { \
          _start = clock(); \
          { __VA_ARGS__; } \
          _stop = clock(); \
          _sum += _stop - _start; \
        } \
        if (ITER > 1) { \
          printf("%s (trung bình %d lượt) = %.5g s\n", \
                NAME, ITER,  (_sum/CLOCKS_PER_SEC) / ITER); \
        } else { \
          printf("%s: %5g s\n", NAME, _sum/CLOCKS_PER_SEC); \
        }\
    } while (0)


#endif  // BASE_CORE_H_
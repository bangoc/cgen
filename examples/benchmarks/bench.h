#ifndef EXAMPLES_BENCHMARKS_BENCH_H_
#define EXAMPLES_BENCHMARKS_BENCH_H_

#include <time.h>

static inline void b_cpu_time_secs(double *data) {
  *data = (double)clock()/CLOCKS_PER_SEC;
}

#define BENCH(NAME, ...)    do {                             \
        double start, stop;                                  \
        b_cpu_time_secs(&start);                             \
        { __VA_ARGS__; }                                     \
        b_cpu_time_secs(&stop);                              \
        printf("%s %.3g\n", NAME, stop - start);             \
    } while (0)

#endif  // EXAMPLES_BENCHMARKS_BENCH_H_
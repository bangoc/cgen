/** (C) Nguyễn Bá Ngọc 2023
 *  cgen version:2.0.0
 */
#ifndef CGEN_H_
#define CGEN_H_

/***** ./base/core.h *****/
#ifndef BASE_CORE_H_
#define BASE_CORE_H_ 
#include <stddef.h>
#include <time.h>
#define CONTAINER_OF(ptr,type,member) \
  ((type *)((void*)(ptr) - offsetof(type, member)))
#define BENCH(NAME,ITER,...) do { \
        double _sum = 0, _start, _stop; \
        for (int _i = 0; _i < (ITER); ++_i) { \
          _start = clock(); \
          { __VA_ARGS__; } \
          _stop = clock(); \
          _sum += _stop - _start; \
        } \
        if ((ITER) > 1) { \
          printf("%s (trung bình %d lượt) = %.5g s\n", \
                (NAME), (ITER), (_sum/CLOCKS_PER_SEC) / (ITER)); \
        } else { \
          printf("%s: %5g s\n", (NAME), _sum/CLOCKS_PER_SEC); \
        }\
    } while (0)
#define BENCH1_START() \
   long _bench1_start = clock()
#define BENCH1_END() \
   long _bench1_end = clock(); \
   printf("Time: %.3f\n", (double)(_bench1_end - _bench1_start)/CLOCKS_PER_SEC)
#endif

/***** ./base/gtype.h *****/
#ifndef BASE_GTYPE_H_
#define BASE_GTYPE_H_ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef union generic_type {
  long l;
  double d;
  char *s;
  void *v;
  struct dlist *dl;
  struct slist *sl;
  struct vector *vec;
  struct treemap *tm;
} gtype;
#define GZERO (GLONG(0l))
#define GTYPE(type,val) ((gtype){.type = (val)})
#define GLONG(value) GTYPE(l, value)
#define GDOUBLE(value) GTYPE(d, value)
#define GSTR(value) GTYPE(s, (char *)value)
#define GVOID(value) GTYPE(v, value)
#define GDLIST(value) GTYPE(dl, value)
#define GSLIST(value) GTYPE(sl, value)
#define GVECTOR(value) GTYPE(vec, value)
#define GTREEMAP(value) GTYPE(tm, value)
#define GSWAP(v1,v2) \
  do { \
    gtype _tmp = (v1); \
    (v1) = (v2); \
    (v2) = _tmp; \
  } while (0)
typedef int (*gtype_cmp_t)(const gtype*, const gtype*);
typedef void (*gtype_free_t)(gtype*);
typedef int (*gtype_print_t)(const gtype*);
static inline int gtype_cmp_l(const gtype *v1, const gtype *v2) {
  return v1->l - v2->l;
}
static inline int gtype_rcmp_l(const gtype *v1, const gtype *v2) {
  return v2->l - v1->l;
}
static inline int gtype_cmp_d(const gtype *v1, const gtype *v2) {
  if (v1->d < v2->d) {
    return -1;
  } else if (v1->d > v2->d) {
    return 1;
  }
  return 0;
}
static inline int gtype_rcmp_d(const gtype *v1, const gtype *v2) {
  if (v2->d < v1->d) {
    return -1;
  } else if (v2->d > v1->d) {
    return 1;
  }
  return 0;
}
static inline int gtype_cmp_s(const gtype *v1, const gtype *v2) {
  return strcmp(v1->s, v2->s);
}
static inline int gtype_rcmp_s(const gtype *v1, const gtype *v2) {
  return strcmp(v2->s, v1->s);
}
static inline int gtype_qsort_l(const void *v1, const void *v2) {
  return ((const gtype*)v1)->l - ((const gtype*)v2)->l;
}
static inline int gtype_qsort_d(const void *v1, const void *v2) {
  if (((const gtype*)v1)->l > ((const gtype*)v2)->l) {
    return 1;
  } else if (((const gtype*)v1)->l < ((const gtype*)v2)->l) {
    return -1;
  }
  return 0;
}
static inline int gtype_qsort_s(const void *v1, const void *v2) {
  return strcmp(((const gtype*)v1)->s, ((const gtype*)v2)->s);
}
static int gtype_print_l(const gtype *value) {
  printf("%ld\n", value->l);
  return 0;
}
static int gtype_print_d(const gtype *value) {
  printf("%f\n", value->d);
  return 0;
}
static int gtype_print_s(const gtype *value) {
  printf("%s\n", value->s);
  return 0;
}
static void gtype_free_s(gtype v) {
  free(v.s);
}
static void gtype_free_v(gtype v) {
  free(v.v);
}
#endif

/***** ./base/flog.h *****/
#ifndef BASE_FLOG_H_
#define BASE_FLOG_H_ 
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#define FLOG_VERSION "1.0.0";
#define FLOG(...) _flog(__FILE__, __LINE__, __VA_ARGS__)
static inline void _flog(const char *file, int line, const char *fmt, ...) {
  const char *filename = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);
  fprintf(stderr, "%s:%d: ", filename, line);
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
  fflush(stderr);
}
#endif

/***** ./cont/vector.h *****/
#ifndef CONT_VECTOR_H_
#define CONT_VECTOR_H_ 
long vsize(const struct vector *v);
int vempty(const struct vector *v);
long vcap(const struct vector *v);
double vratio(const struct vector *v);
gtype_free_t vfv(const struct vector *v);
struct vector *vsetfv(struct vector *v, gtype_free_t fv);
gtype *varr(struct vector *v);
gtype *vref(struct vector *v, long i);
long vidx(struct vector *v, gtype *elem_ptr);
struct vector *vreserve(struct vector *v, long newcap);
struct vector *vresize(struct vector *v, long newsz);
struct vector *vappend(struct vector *v, gtype val);
struct vector *vremove(struct vector *v, long idx);
struct vector *vclear(struct vector *v);
void vfree(struct vector *v);
void vfill(struct vector *v, gtype value);
void gfree_vec(gtype *value);
struct vector *vpush(struct vector *v, gtype val);
struct vector *vpop(struct vector *v);
gtype *vtop(struct vector *v);
struct vector *vcreate(long sz);
struct vector *vclone(struct vector *v);
int vsameas(struct vector *v1, struct vector *v2);
#define VTRAVERSE(cur,v) \
  for (gtype *cur = varr(v), *end = varr(v) + vsize(v); \
    cur < end; ++cur)
#define VRTRAVERSE(cur,v) \
  for (gtype *beg = varr(v), *cur = varr(v) + vsize(v) -1; \
    cur >= beg; --cur)
#define VSORT(v,cmp) \
  qsort(varr(v), vsize(v), sizeof(gtype), cmp)
#endif

/***** ./cont/queue.h *****/
#ifndef CONT_QUEUE_H_
#define CONT_QUEUE_H_ 
struct queue *qcreate(long cap);
struct queue *qenque(struct queue* q, gtype val);
struct queue *qdeque(struct queue *q);
gtype *qpeek(struct queue *q);
int qempty(const struct queue *q);
long qsize(const struct queue *q);
long qnext(const struct queue *q, long id);
void qfree(struct queue *q);
gtype_free_t qfv(struct queue *q);
struct queue *qsetfv(struct queue *q, gtype_free_t fv);
#endif

/***** ./cont/slist.h *****/
#ifndef CONT_SLIST_H_
#define CONT_SLIST_H_ 
struct slist *screate();
gtype *sfront(struct slist *list);
gtype *sback(struct slist *list);
long ssize(struct slist *list);
gtype_free_t sfv(struct slist *list);
struct slist *ssetfv(struct slist *list, gtype_free_t fv);
void sfree(struct slist *list);
int sempty(struct slist *list);
struct slist *sappend(struct slist *list, gtype data);
struct slist *sprepend(struct slist *list, gtype data);
struct slist *sdfront(struct slist *list);
struct slist *spush(struct slist *list, gtype elem);
struct slist *spop(struct slist *list);
gtype *stop(struct slist *list);
struct slist *senque(struct slist *list, gtype elem);
struct slist *sdeque(struct slist *list);
gtype *speek(struct slist *list);
#define STRAVERSE(cur,list) \
  for (gtype *cur = (gtype*)sfront(list); cur != NULL; \
              cur = (gtype*)((struct snode*)cur)->next)
#endif

/***** ./cont/dlist.h *****/
#ifndef CONT_DLIST_H_
#define CONT_DLIST_H_ 
struct dlist *dcreate();
gtype *dfront(struct dlist *list);
gtype *dback(struct dlist *list);
long dsize(struct dlist *list);
int dempty(struct dlist *list);
void dfree(struct dlist *list);
void dclear(struct dlist *list);
struct dlist *dappend(struct dlist *list, gtype elem);
struct dlist *dprepend(struct dlist *list, gtype elem);
struct dlist *ddfront(struct dlist *list);
struct dlist *ddback(struct dlist *list);
gtype_free_t dfv(struct dlist *list);
struct dlist *dsetfv(struct dlist *list, gtype_free_t fv);
#define DTRAVERSE(cur,list) \
  for (gtype *cur = (gtype*)((list)->front); cur != NULL; \
              cur = (gtype*)((struct dnode *)cur->next))
#define DRTRAVERSE(cur,list) \
  for (gtype *cur = (gtype*)((list)->back); cur != NULL; \
              cur = (gtype*)((struct dnode *)cur->prev))
#endif
#endif  // CGEN_H_
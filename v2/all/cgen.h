/** (C) Nguyễn Bá Ngọc 2023
 *  cgen version:2.0.0
 */
#ifndef CGEN_H_
#define CGEN_H_

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
} gtype;
#define GZERO (GLONG(0l))
#define GTYPE(type,val) ((gtype){.type = (val)})
#define GLONG(value) GTYPE(l, value)
#define GDOUBLE(value) GTYPE(d, value)
#define GSTR(value) GTYPE(s, value)
#define GVOID(value) GTYPE(v, value)
#define GCALL2(func,cont,value) \
    _Generic((value), \
        char: func##_l, \
        short: func##_l, \
        int: func##_l, \
        long: func##_l, \
        float: func##_d, \
        double: func##_d, \
        char *: func##_s, \
        gtype: func, \
        default: func##_v)(cont, value)
#define VALUE(elem,member) _Generic((elem),\
        gtype: gget_##member,\
        gtype*: pgget_##member)(elem)
#define LONGG(elem) VALUE(elem, l)
#define DOUBLEG(elem) VALUE(elem, d)
#define STRG(elem) VALUE(elem, s)
#define VOIDG(elem) VALUE(elem, v)
static inline long gget_l(gtype g) { return g.l; }
static inline double gget_d(gtype g) { return g.d; }
static inline char *gget_s(gtype g) { return g.s; }
static inline void *gget_v(gtype g) { return g.v; }
static inline long pgget_l(gtype *g) { return g->l; }
static inline double pgget_d(gtype *g) { return g->d; }
static inline char *pgget_s(gtype *g) { return g->s; }
static inline void *pgget_v(gtype *g) { return g->v; }
#define GSWAP(v1,v2) \
  do { \
    gtype _tmp = (v1); \
    (v1) = (v2); \
    (v2) = _tmp; \
  } while (0)
typedef int (*gcmp_fn_t)(const gtype, const gtype);
typedef int (*gprint_fn_t)(const gtype);
typedef void (*free_fn_t)();
static inline int glong_cmp(const gtype v1, const gtype v2) {
  return v1.l - v2.l;
}
static inline int glong_rcmp(const gtype v1, const gtype v2) {
  return v2.l - v1.l;
}
static inline int gdouble_cmp(const gtype v1, const gtype v2) {
  if (v1.d < v2.d) {
    return -1;
  } else if (v1.d > v2.d) {
    return 1;
  }
  return 0;
}
static inline int gdouble_rcmp(const gtype v1, const gtype v2) {
  if (v2.d < v1.d) {
    return -1;
  } else if (v2.d > v1.d) {
    return 1;
  }
  return 0;
}
static inline int gstr_cmp(const gtype v1, const gtype v2) {
  return strcmp(v1.s, v2.s);
}
static inline int gstr_rcmp(const gtype v1, const gtype v2) {
  return strcmp(v2.s, v1.s);
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
static int gtype_print_l(const gtype value) {
  printf("%ld\n", value.l);
  return 0;
}
static int gtype_print_d(const gtype value) {
  printf("%f\n", value.d);
  return 0;
}
static int gtype_print_s(const gtype value) {
  printf("%s\n", value.s);
  return 0;
}
#endif

/***** ./base/flog.h *****/
#ifndef BASE_FLOG_H_
#define BASE_FLOG_H_ 
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#define FLOG_VERSION "1.0.0";
#ifdef CGEN_DEBUG
  #define FLOG(...) _flog(__FILE__, __LINE__, __VA_ARGS__)
#else
  #define FLOG(...)
#endif
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

/***** ./cont/arr.h *****/
#ifndef CONT_ARR_H_
#define CONT_ARR_H_ 
#include <stdlib.h>
struct ainfo {
  void *elems;
  long size;
  long cap;
  long esz;
  double rio;
};
static inline void *acreate_internal(long size, long esz, double rio) {
  long cap = size > 0? size: 8;
  struct ainfo *info = malloc(sizeof(struct ainfo));
  info->elems = malloc(cap * esz);
  info->size = size;
  info->cap = cap;
  info->esz = esz;
  info->rio = rio;
  return &info->elems;
}
#define acreate(elemtype,size) \
   acreate_internal(size, sizeof(elemtype), 2.0)
#define adecl(elemtype,name) elemtype **name
#define amake(elemtype,name,size) \
   adecl(elemtype, name) = acreate(elemtype, size)
#define ainfo(a) ((struct ainfo *)(a))
#define asize(a) (ainfo(a)->size)
#define acap(a) (ainfo(a)->cap)
#define aesz(a) (ainfo(a)->esz)
#define ario(a) (ainfo(a)->rio)
#define aarr(a) (*(a))
#define aelem(a,i) aarr(a)[i]
#define areserve(a,newcap) \
  do { \
    if ((newcap) < asize(a)) { \
      break; \
    } \
    struct ainfo *_info = ainfo(a); \
    _info->elems = realloc(_info->elems, (newcap) * _info->esz); \
    _info->cap = (newcap); \
    *(a) = _info->elems; \
  } while (0)
#define aresize(a,newsize) \
  do { \
    if (newsize > acap(a)) { \
      areserve((a), newsize); \
    } \
    asize(a) = (newsize); \
  } while (0)
#define afree(a) \
    free(*(a)); \
    free(ainfo(a))
#define aclear(a) \
  do { \
    aresize(a, 0); \
    areserve(a, 8); \
  } while (0)
#define aappend(a,elem) \
   do { \
     struct ainfo *_info = ainfo(a); \
     if (_info->size >= _info->cap) { \
       long _newcap = _info->cap * _info->rio; \
       areserve((a), _newcap); \
       _info = ainfo(a); \
     } \
     (*(a))[_info->size++] = (elem); \
   } while (0)
#define ainsertb(a,elem,pos) \
   do { \
     long _pos = (pos); \
     struct ainfo *_info = ainfo(a); \
     aresize(a, _info->size + 1); \
     _info = ainfo(a); \
     for (long _i = _info->size - 1; _i > _pos; --_i) { \
        aelem(a, _i) = aelem(a, _i - 1); \
     } \
     aelem(a, _pos) = elem; \
     printf("pos: %ld\n", _pos); \
   } while (0)
#define aqsort(a,cmp) \
   qsort(*(a), asize(a), aesz(a), cmp)
#define afor(i,a) \
  for (long i = 0; i < asize(a); ++i)
#define aremove(a,pos) \
    do { \
      if (asize(a) == 0) { \
        break; \
      } \
      for (long _i = (pos); _i < asize(a) - 1; ++_i) { \
        aelem(a, _i) = aelem(a, _i + 1); \
      } \
      --asize(a); \
    } while (0)
#define apush(a,elem) aappend(a, elem)
#define atop(a) aelem(a, asize(a) - 1)
#define apop(a) \
  do { \
    struct ainfo *_info = ainfo(a); \
    aremove(a, _info->size - 1); \
    if (_info->cap / (_info->size + 1) > 8) { \
      areserve(a, _info->size + 8); \
    } \
  } while (0)
#define aenque(a,elem) aappend(a, elem)
#define apeek(a,head) aelem(a, head)
#define adeque(a,head) \
    do { \
      struct ainfo *_info = ainfo(a); \
      if (head >= _info->size) { \
        break; \
      } \
      ++head; \
      if (head / (_info->cap - head + 1) > 8) { \
        for (long _i = head; _i < _info->size; ++_i) { \
          aelem(a, _i - head) = aelem(a, _i); \
        } \
        aresize(a, _info->size - head); \
        areserve(a, _info->size + 8); \
        head = 0; \
      } \
    } while (0)
#endif

/***** ./cont/vector.h *****/
#ifndef CONT_VECTOR_H_
#define CONT_VECTOR_H_ 
struct vector;
long vsize(const struct vector *v);
int vempty(const struct vector *v);
long vcap(const struct vector *v);
double vratio(const struct vector *v);
free_fn_t vfv(const struct vector *v);
struct vector *vsetfv(struct vector *v, free_fn_t fv);
gtype *varr(struct vector *v);
gtype *vref(struct vector *v, long i);
long vidx(struct vector *v, gtype *elem_ptr);
struct vector *vreserve(struct vector *v, long newcap);
struct vector *vresize(struct vector *v, long newsz);
struct vector *_vappend(struct vector *v, gtype val);
#define vappend(v,elem) GCALL2(_vappend, v, elem)
static inline struct vector *_vappend_l(struct vector *v, long elem) {
  return _vappend(v, GLONG(elem));
}
static inline struct vector *_vappend_d(struct vector *v, double elem) {
  return _vappend(v, GDOUBLE(elem));
}
static inline struct vector *_vappend_s(struct vector *v, char *elem) {
  return _vappend(v, GSTR(elem));
}
static inline struct vector *_vappend_v(struct vector *v, void *elem) {
  return _vappend(v, GVOID(elem));
}
struct vector *vremove(struct vector *v, long idx);
struct vector *vinsert_before(struct vector *v, gtype e, long i);
struct vector *vclear(struct vector *v);
void vfree(struct vector *v);
void vfill(struct vector *v, gtype value);
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
struct queue;
struct queue *qcreate(long cap);
struct queue *qenque(struct queue* q, gtype val);
struct queue *qdeque(struct queue *q);
gtype *qpeek(struct queue *q);
int qempty(const struct queue *q);
long qsize(const struct queue *q);
long qnext(const struct queue *q, long id);
void qfree(struct queue *q);
free_fn_t qfv(struct queue *q);
struct queue *qsetfv(struct queue *q, free_fn_t fv);
#endif

/***** ./cont/slist.h *****/
#ifndef CONT_SLIST_H_
#define CONT_SLIST_H_ 
struct slist;
struct slist *screate();
gtype *sfront(struct slist *list);
gtype *sback(struct slist *list);
long ssize(struct slist *list);
free_fn_t sfv(struct slist *list);
struct slist *ssetfv(struct slist *list, free_fn_t fv);
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
struct dlist;
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
free_fn_t dfv(struct dlist *list);
struct dlist *dsetfv(struct dlist *list, free_fn_t fv);
#define DTRAVERSE(cur,list) \
  for (gtype *cur = (gtype*)((list)->front); cur != NULL; \
              cur = (gtype*)((struct dnode *)cur->next))
#define DRTRAVERSE(cur,list) \
  for (gtype *cur = (gtype*)((list)->back); cur != NULL; \
              cur = (gtype*)((struct dnode *)cur->prev))
#endif

/***** ./cont/tmap.h *****/
#ifndef CONT_TREEMAP_H_
#define CONT_TREEMAP_H_ 
struct tnode;
struct tmap;
gtype *tkey_of(struct tnode *n);
gtype *tvalue_of(struct tnode *n);
struct tnode *tleft_most(struct tnode *n);
struct tnode *tright_most(struct tnode *n);
struct tnode *tleft_deepest(struct tnode *n);
struct tnode *tnext_lrn(struct tnode *x);
void tnextkv_lrn(gtype **pk, gtype **pv);
struct tnode *tprev_lnr(struct tnode *x);
void tprevkv_lnr(gtype **pk, gtype **pv);
struct tnode *tnext_lnr(struct tnode *x);
void tnextkv_lnr(gtype **k, gtype **v);
int tis_red(struct tnode *n);
int tis_black(struct tnode *n);
struct tnode *tleft_of(struct tnode *n);
struct tnode *tright_of(struct tnode *n);
struct tnode *ttop_of(struct tnode *n);
struct tmap *tcreate(gcmp_fn_t cmp);
gtype *tput(struct tmap *t, const gtype key, const gtype value);
gtype *tget(struct tmap *t, const gtype key);
struct tmap *tremove(struct tmap *t, gtype key);
long tsize(const struct tmap *t);
struct tnode *troot(struct tmap *t);
free_fn_t tfk(struct tmap *t);
free_fn_t tfv(struct tmap *t);
struct tmap *tsetfk(struct tmap *t, free_fn_t fk);
struct tmap *tsetfv(struct tmap *t, free_fn_t fv);
void tfree(struct tmap *t);
#define TTRAVERSE_LNR(k,v,t) \
  for (gtype *k = (gtype*)tleft_most(troot(t)), \
             *v = k? tvalue_of((struct tnode*)k): NULL; \
       k != NULL && v != NULL; tnextkv_lnr(&k, &v))
#define TTRAVERSE(k,v,t) TTRAVERSE_LNR(k, v, t)
#define TTRAVERSE_RNL(k,v,t) \
  for (gtype *k = (gtype*)tright_most(troot(t)), \
             *v = k? tvalue_of((struct tnode*)k): NULL; \
       k != NULL && v != NULL; tprevkv_lnr(&k, &v))
#define TRTRAVERSE(k,v,t) TTRAVERSE_RNL(k, v, t)
#define TTRAVERSE_LRN(k,v,t) \
  for (gtype *k = (gtype*)tleft_deepest(troot(t)), \
             *v = k? tvalue_of((struct tnode *)k): NULL; \
       k != NULL; tnextkv_lrn(&k, &v))
#endif

/***** ./algo/perm.h *****/
#ifndef ALGO_PERM_H_
#define ALGO_PERM_H_ 
struct vector *create_perm(long n);
struct vector *next_perm(struct vector *v);
struct vector *prev_perm(struct vector *v);
int has_next_perm(struct vector *v);
int has_prev_perm(struct vector *v);
#endif

/***** ./utils/bench.h *****/
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
#endif  // CGEN_H_

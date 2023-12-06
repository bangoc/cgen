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
static inline gtype gtype_from_long(long value) {
  return (gtype){.l = value};
}
static inline gtype gtype_from_double(double value) {
  return (gtype){.d = value};
}
static inline gtype gtype_from_str(char *value) {
  return (gtype){.s = value};
}
static inline gtype gtype_from_void(void *value) {
  return (gtype){.v = value};
}
static inline gtype gtype_from_gtype(gtype value) {
  return value;
}
#define GTYPE(value) \
    _Generic((value), \
        char: gtype_from_long, \
        short: gtype_from_long, \
        int: gtype_from_long, \
        long: gtype_from_long, \
        float: gtype_from_double, \
        double: gtype_from_double, \
        char *: gtype_from_str, \
        gtype: gtype_from_gtype, \
        default: gtype_from_void \
    )(value)
#define GZERO (GTYPE(0l))
#define GSWAP(v1,v2) \
  do { \
    gtype _tmp = (v1); \
    (v1) = (v2); \
    (v2) = _tmp; \
  } while (0)
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

/***** ./base/fnt.h *****/
#ifndef BASE_FNT_H_
#define BASE_FNT_H_ 
#include <string.h>
typedef int (*compare_fnt)(const void *p1, const void *p2);
typedef void (*destructor_fnt)(void *p);
static inline int cmpl(const void *p1, const void *p2) {
  return *(const int*)p1 - *(const int*)p2;
}
static inline int rcmpl(const void *p1, const void *p2) {
  return *(const int*)p2 - *(const int*)p1;
}
static inline int cmpd(const void *p1, const void *p2) {
  double v1 = *(const double *)p1, v2 = *(const double *)p2;
  if (v1 < v2) {
    return - 1;
  } else if (v1 > v2) {
    return 1;
  }
  return 0;
}
static inline int rcmpd(const void *p1, const void *p2) {
  double v2 = *(const double *)p1, v1 = *(const double *)p2;
  if (v1 < v2) {
    return - 1;
  } else if (v1 > v2) {
    return 1;
  }
  return 0;
}
static inline int cmps(const void *p1, const void *p2) {
  char *const *s1 = p1, *const *s2 = p2;
  return strcmp(*s1, *s2);
}
static inline int rcmps(const void *p1, const void *p2) {
  char *const *s2 = p1, *const *s1 = p2;
  return strcmp(*s1, *s2);
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
destructor_fnt vfv(const struct vector *v);
struct vector *vsetfv(struct vector *v, destructor_fnt fv);
gtype *varr(struct vector *v);
#define velem(v,i) varr(v)[i]
gtype *vref(struct vector *v, long i);
long vidx(struct vector *v, gtype *elem_ptr);
struct vector *vreserve(struct vector *v, long newcap);
struct vector *vresize(struct vector *v, long newsz);
struct vector *_vappend(struct vector *v, gtype val);
#define vappend(v,elem) _vappend(v, GTYPE(elem))
struct vector *vremove(struct vector *v, long idx);
struct vector *_vinsertb(struct vector *v, gtype e, long i);
#define vinsertb(v,e,i) _vinsertb(v, GTYPE(e), i)
struct vector *vclear(struct vector *v);
void vfree(void *op);
void _vfill(struct vector *v, gtype value);
#define vfill(v,value) _vfill(v, GTYPE(value))
#define vpush(v,val) vappend(v, val)
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
struct queue *_qenque(struct queue* q, gtype val);
#define qenque(q,val) _qenque(q, GTYPE(val))
struct queue *qdeque(struct queue *q);
gtype *qpeek(struct queue *q);
int qempty(const struct queue *q);
long qsize(const struct queue *q);
long qnext(const struct queue *q, long id);
void qfree(void *op);
destructor_fnt qfv(struct queue *q);
struct queue *qsetfv(struct queue *q, destructor_fnt fv);
#endif

/***** ./cont/slist.h *****/
#ifndef CONT_SLIST_H_
#define CONT_SLIST_H_ 
struct slist;
struct slist *screate();
gtype *sfront(struct slist *list);
gtype *sback(struct slist *list);
long ssize(struct slist *list);
destructor_fnt sfv(struct slist *list);
struct slist *ssetfv(struct slist *list, destructor_fnt fv);
void sfree(void *op);
int sempty(struct slist *list);
struct slist *_sappend(struct slist *list, gtype data);
#define sappend(list,data) _sappend(list, GTYPE(data))
struct slist *_sprepend(struct slist *list, gtype data);
#define sprepend(list,data) _sprepend(list, GTYPE(data))
struct slist *sdfront(struct slist *list);
#define spush(list,elem) sprepend(list, elem)
#define spop(list) sdfront(list)
gtype *stop(struct slist *list);
#define senque(list,elem) sappend(list, elem)
#define sdeque(list) sdfront(list)
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
void dfree(void *op);
void dclear(struct dlist *list);
struct dlist *_dappend(struct dlist *list, gtype elem);
#define dappend(list,elem) _dappend(list, GTYPE(elem))
struct dlist *_dprepend(struct dlist *list, gtype elem);
#define dprepend(list,elem) _dprepend(list, GTYPE(elem))
struct dlist *ddfront(struct dlist *list);
struct dlist *ddback(struct dlist *list);
destructor_fnt dfv(struct dlist *list);
struct dlist *dsetfv(struct dlist *list, destructor_fnt fv);
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
struct tmap *tcreate(compare_fnt cmp);
struct tmap *tconstruct(compare_fnt cmp, destructor_fnt fk, destructor_fnt fv);
gtype *_tput(struct tmap *t, const gtype key, const gtype value);
#define tput(t,k,v) _tput(t, GTYPE(k), GTYPE(v))
gtype *_tget(struct tmap *t, const gtype key);
#define tget(t,key) _tget(t, GTYPE(key))
struct tmap *_tremove(struct tmap *t, gtype key);
#define tremove(t,key) _tremove(t, GTYPE(key))
long tsize(const struct tmap *t);
struct tnode *troot(struct tmap *t);
destructor_fnt tfk(struct tmap *t);
destructor_fnt tfv(struct tmap *t);
struct tmap *tsetfk(struct tmap *t, destructor_fnt fk);
struct tmap *tsetfv(struct tmap *t, destructor_fnt fv);
void tfree(void *op);
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

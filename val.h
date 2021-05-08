#ifndef VAL_H_
#define VAL_H_

typedef union gtype {
  long l;
  double d;
  char *s;
  void *v;
} *value_t;

#endif  // VAL_H_
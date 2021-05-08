/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef GTYPE_H_
#define GTYPE_H_

typedef union {
  long i;
  double d;
  char *s;
  void *v;
} gtype;

#define INVALID_VALUE ((gtype){.i = -1})

#endif  // GTYPE_H_
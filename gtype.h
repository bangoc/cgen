/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef GTYPE_H_
#define GTYPE_H_

typedef union {
  long l;
  double d;
  char *s;
  void *v;
} gtype;

#endif  // GTYPE_H_
/* (C) Nguyen Ba Ngoc 2022 */

#include "utils/str.h"

#include <string.h>

const char* ascii_spaces = "\t\n\v\f\r ";

struct gvector *str_tokens(char *line, const char *delims) {
#ifndef CGEN_USE_GC
  struct gvector *tokens = gvec_create(0, NULL);
#else  // CGEN_USE_GC
  struct gvector *tokens = gvec_create(0);
#endif  // CGEN_USE_GC
  tok_traverse(tk, line, delims) {
    gvec_append(tokens, gtype_s(tk));
  }
  return tokens;
}
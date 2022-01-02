/*
  (C) Nguyen Ba Ngoc 2022
*/

#include "str.h"

#include <string.h>

const char* ascii_spaces = "\t\n\v\f\r ";

gvec_t str_tokens(char *line, const char *delims) {
  gvec_t tokens = gvec_create(5, NULL);
  tok_traverse(tk, line, delims) {
    gvec_append(tokens, gtype_s(tk));
  }
  return tokens;
}
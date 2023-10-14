/* (C) Nguyen Ba Ngoc 2022 */

#include "utils/str.h"

#include <string.h>

const char* ascii_spaces = "\t\n\v\f\r ";

struct vector *str_tokens(char *line, const char *delims) {
  struct vector *tokens = vcreate(0);
  tok_traverse(tk, line, delims) {
    vappend(tokens, gtype_s(tk));
  }
  return tokens;
}
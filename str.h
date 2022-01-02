#ifndef STR_H_
#define STR_H_

/*
  (C) Nguyen Ba Ngoc 2022
*/

#include "gvec.h"

extern const char* ascii_spaces;

gvec_t str_tokens(char *line, const char *delims);

#define str_split(line) str_tokens(line, ascii_spaces)

#endif  // STR_H_
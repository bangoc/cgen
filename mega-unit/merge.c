/* (C) Nguyen Ba Ngoc 2022 */

#include "all.h"

#include <stdlib.h>
#include <string.h>

int is_include(const char *line) {
  return strstr(line, "#include ") == line;
}

gvec_t read_lines(const char *fname) {
  FILE *fp = fopen(fname, "r");
  if (!fp) {
    return NULL;
  }
  gvec_t lines = gvec_create(100, gtype_free_s);
  char *tmp = NULL;
  while (cgetline(&tmp, NULL, fp)) {
    remove_tail_lf(tmp);
    gvec_append(lines, gtype_s(strdup(tmp)));
  }
  fclose(fp);
  free(tmp);
  return lines;
}

char *parse_include(const char *line) {
  const char *p1 = strchr(line, '"');
  if (!p1) {
    return NULL;
  }
  const char *p2 = strchr(p1 + 1, '"');
  char *name = calloc(p2 - p1, 1);
  strncpy(name, p1 + 1, p2 - p1 - 1);
  return name;
}

int is_copyright(const char *line) {
  return strstr(line, "/* (C)") == line;
}

int is_header(const char *fname) {
  return !strcmp(fname + strlen(fname) - 2, ".h");
}

char *header_guard(const char *fname) {
  char *o = calloc(strlen(fname) + 2, 1);
  for (int i = 0; i < strlen(fname); ++i) {
    if (fname[i] == '.') {
      o[i] = '_';
      continue;
    }
    o[i] = toupper(fname[i]);
  }
  return o;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: merge root-dir listing out-name\n"
           "Example: merge ~/git/cgen all.h cgen.h\n");
    return 1;
  }
  const char *root = argv[1],
             *list = argv[2],
             *out_name = argv[3];
  char tmp[1024] = {0};
  strcat(tmp, root);
  strcat(tmp, "/");
  strcat(tmp, list);
  gvec_t v = read_lines(tmp);
  if (!v) {
    printf("Can not read the list\n");
    return 1;
  }

  rbs_t headers = rbs_create(gtype_cmp_s, gtype_free_s);
  gvec_t contents = gvec_create(1000, gtype_free_s);
  gvec_traverse(cur, v) {
    if (!is_include(cur->s)) {
      continue;
    }
    char *unit_name = parse_include(cur->s);
    tmp[0] = 0;
    strcat(tmp, root);
    strcat(tmp, "/");
    strcat(tmp, unit_name);
    gvec_t loc = read_lines(tmp);
    char origin[1024];
    sprintf(origin, "\n/***********************************\n"
                    " * %s\n"
                    " ***********************************/\n\n", unit_name);
    gvec_append(contents, gtype_s(strdup(origin)));
    gvec_traverse(cur, loc) {
      if (is_include(cur->s)) {
        char *line = strdup(cur->s);
        if (!rbs_insert(headers, gtype_s(line))) {
          free(line);
        }
        continue;
      }
      if (is_copyright(cur->s)) {
        continue;
      }
      gvec_append(contents, gtype_s(strdup(cur->s)));
    }
    gvec_free(loc);
    free(unit_name);
  }
  char *hg = NULL;
  FILE *out = fopen(out_name, "w");
  if (!out) {
    printf("Không thể mở tệp đầu ra.\n");
    return 1;
  }
  if (is_header(out_name)) {
    hg = header_guard(out_name);
    fprintf(out, "#ifndef %s\n", hg);
    fprintf(out, "#define %s\n\n", hg);
  }
  fprintf(out, "/* (C) Nguyen Ba Ngoc 2022 */\n\n");
  rbs_traverse(cur, headers) {
    fprintf(out, "%s\n", cur->s);
  }
  gvec_traverse(cur, contents) {
    fprintf(out, "%s\n", cur->s);
  }
  if (is_header(out_name)) {
    fprintf(out, "\n#endif  // %s\n", hg);
    free(hg);
  }
  gvec_free(contents);
  rbs_free(headers);
  gvec_free(v);
  fclose(out);
  return 0;
}
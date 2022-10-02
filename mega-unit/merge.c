/* (C) Nguyen Ba Ngoc 2022 */

#include "all.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int is_include(const char *line) {
  return strstr(line, "#include ") == line;
}

struct gvector *read_lines(const char *fname) {
  FILE *fp = fopen(fname, "r");
  if (!fp) {
    printf("Lỗi mở tệp %s\n", fname);
    return NULL;
  }
  struct gvector *lines = gvec_create_full(0, 100, gtype_zero, gtype_free_s);
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

int is_source(const char *fname) {
  return !strcmp(fname + strlen(fname) - 2, ".c");
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
  o[strlen(fname)] = '_';
  return o;
}

char *get_version(const char *root) {
  char fname[1024];
  sprintf(fname, "%s/%s", root, "VERSION");
  FILE *fp = fopen(fname, "r");
  if (!fp) {
    return NULL;
  }
  char *vstr = NULL;
  remove_tail_lf(cgetline(&vstr, NULL, fp));
  fclose(fp);
  return vstr;
}

void process(const char *root, const char *list_name, const char *out_name) {
  struct gvector *v = read_lines(list_name);
  if (!v) {
    printf("Can not read the list\n");
    return;
  }

  struct rbstree *headers = rbs_create(gtype_cmp_s, gtype_free_s);
  struct gvector *contents = gvec_create_full(0, 1000, gtype_zero, gtype_free_s);
  char tmp[1024];
  gvec_traverse(cur, v) {
    if (!is_include(cur->s)) {
      continue;
    }
    char *unit_name = parse_include(cur->s);
    sprintf(tmp, "%s/%s", root, unit_name);
    struct gvector *loc = read_lines(tmp);
    char origin[1024];
    sprintf(origin, "\n/***********************************\n"
                    " * %s\n"
                    " ***********************************/", unit_name);
    gvec_append(contents, gtype_s(strdup(origin)));
    gvec_append(contents, gtype_s(strdup("")));
    gvec_traverse(cur, loc) {
      if (is_include(cur->s)) {
        if (strchr(cur->s, '"')) {
          continue;
        }
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
    return;
  }
  char *ver = get_version(root);
  if (is_header(out_name)) {
    hg = header_guard(out_name);
    fprintf(out, "#ifndef %s\n", hg);
    fprintf(out, "#define %s\n\n", hg);
  }
  fprintf(out, "/* (C) Nguyen Ba Ngoc 2022 */\n");
  if (ver) {
    fprintf(out, "/* Version: %s */\n\n", ver);
    free(ver);
  }
  if (is_source(out_name)) {
    char *hn = strdup(out_name);
    hn[strlen(hn) - 1] = 'h';
    fprintf(out, "#include \"%s\"\n\n", hn);
    free(hn);
  }
  rbs_traverse(cur, headers) {
    fprintf(out, "%s\n", cur->s);
  }
  int blanks = 0;
  gvec_traverse(cur, contents) {
    if (strcmp(cur->s, "") == 0) {
      if (++blanks > 1) {
        continue;
      }
    } else {
      blanks = 0;
    }
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
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: merge root-dir file-list output-name\n"
           "Example: merge ~/git/cgen all.h all.c cgen\n"
           "Trong đó:\n"
           "\t~/git/cgen: Thư mục gốc\n"
           "\tall.h: Tên tệp chưa danh sách tệp cần được hợp nhất, đường dẫn tương đối\n"
           "\toutput-name: Tên tệp đầu ra\n");
    return 1;
  }
  const char *root = argv[1],
             *list = argv[2],
             *oname = argv[3];
  char list_name[1024] = {0};
  sprintf(list_name, "%s/%s", root, list);
  process(root, list_name, oname);
  return 0;
}
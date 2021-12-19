/* Hỗ trợ biên dịch với gcc */
#include "cgen.ic"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 300

typedef struct song_s {
  char name[N];
} *song_t;

gtype create_song_g(const char *name) {
  song_t s = malloc(sizeof(struct song_s));
  strcpy(s->name, name);
  return (gtype){.v = (void*)s};
}

int main() {
  dll_t list = dll_create_list(dll_free_node);

  // Add songs to list
  gdl_push_back(list, create_song_g("Seasons in the sun"));
  gdl_push_back(list, create_song_g("Black or White"));
  gdl_push_front(list, create_song_g("Beautiful in white"));
  gdl_inserta(list, list->front, create_song_g("Lemon tree"));
  gdl_insertb(list, list->back, create_song_g("Opera No 2"));

  // Print songs list
  int stt = 1;
  dll_traverse(cur, list) {
    song_t s = (song_t)(gdn_value(cur).v);
    printf("%3d %s\n", stt++, s->name);
  }

  // Free memory
  dll_traverse(cur, list) {
    free(gdn_value(cur).v);
  }
  dll_free_list(list);
  return 0;
}

/* Hỗ trợ biên dịch với gcc */
#include "all.h"

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

void free_song_g(gtype g) {
  free(g.v);
}

int main() {
  struct gdllist *list = gdl_create_list(free_song_g);

  // Add songs to list
  gdl_push_back(list, create_song_g("Seasons in the sun"));
  gdl_push_back(list, create_song_g("Black or White"));
  gdl_push_front(list, create_song_g("Beautiful in white"));
  gdl_inserta(list, gdl_front(list), create_song_g("Lemon tree"));
  gdl_insertb(list, gdl_back(list), create_song_g("Opera No 2"));

  // Print songs list
  int stt = 1;
  gdl_traverse(cur, list) {
    song_t s = (song_t)(cur->v);
    printf("%3d %s\n", stt++, s->name);
  }

  gdl_free(list);
  return 0;
}

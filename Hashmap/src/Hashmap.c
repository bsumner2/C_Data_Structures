#include "Hashmap.h"
#include <stdlib.h>
#include <string.h>


/** 
 * @brief REQUIRES null-terminated key */
static int hash(const char* key) {
  unsigned long ret = 5381;
  char curr;
  while ((curr = *(key++)))
    ret = ((ret<<5) + ret) ^ curr;
  return ret%7919;
}

Hashmap *HashmapCreate(void) {
  return (Hashmap*)calloc(1, sizeof(Hashmap));
}

void HashmapPut(Hashmap *map, const char *key, void *value, size_t size) {
  int idx;
  HBNode *curr;
  if (!map || !key || !value)
    return;

  idx = hash(key);
  curr = map->table[idx];
  if (!curr) {
    curr = (HBNode*)calloc(1, sizeof(HBNode));
    strncpy(curr->key, key, MAX_HASHMAP_KEY_LEN);
    curr->value = malloc(size);
    memmove(curr->value, value, size);
    map->table[idx] = curr;
    return;
  }

  while (curr->nxt) {
    if (!strcmp(curr->key, key)) {
      curr->value = realloc(curr->value, size);
      memmove(curr->value, value, size);
      return;
    }
    curr = curr->nxt;
  }
  if (!strcmp(curr->key, key)) {
    curr->value = realloc(curr->value, size);
    memmove(curr->value, value, size);
    return;
  }
  curr->nxt = (HBNode*)calloc(1, sizeof(HBNode));
  strncpy(curr->nxt->key, key, MAX_HASHMAP_KEY_LEN);
  curr->nxt->value = malloc(size);
  memmove(curr->nxt->value, value, size);

}

void *HashmapGet(Hashmap *map, const char *key) {
  int idx;
  HBNode *curr;
  if (!map || !key)
    return NULL;
  idx = hash(key);
  curr = map->table[idx];
   
  while (curr) {
    if (!strcmp(curr->key, key))
      return curr->value;
    curr = curr->nxt;
  }

  return NULL;
}


u8 HashmapRemove(Hashmap *map, const char *key) {
  int idx;
  HBNode *curr, *prev;
  if (!map || !key)
    return 0;
  idx = hash(key);
  if (!(curr = map->table[idx]))
    return 0;
  if (!strcmp(curr->key, key)) {
    map->table[idx] = curr->nxt;
    free(curr->value);
    free(curr);
    return 1;
  }
  prev = curr;
  curr = curr->nxt;
  while (curr) {
    if (!strcmp(curr->key, key)) {
      prev->nxt = curr->nxt;
      free(curr->value);
      free(curr);
      return 1;
    }
    prev = curr;
    curr = curr->nxt;

  }
  return 0;
}


void *HashmapFree(Hashmap *map) {
  int i;
  HBNode *curr;
  HBNode *tmp;
  if (!map)
    return NULL;
  for (i = 0; i < 7919; ++i) {
    if (!(curr = map->table[i]))
      continue;
    while ((tmp = curr)) {
      curr = curr->nxt;
      free(tmp->value);
      free(tmp);
    }
    map->table[i] = NULL;
  }

  free(map);
  return NULL;

}

#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <stddef.h>
#include <stdio.h>

typedef unsigned char u8;

#define MAX_HASHMAP_KEY_LEN 256



typedef struct _HBNode {
  char key[MAX_HASHMAP_KEY_LEN];
  void* value;
  struct _HBNode *nxt;
} HBNode;


typedef struct {
  HBNode *table[7919];
} Hashmap;


Hashmap *HashmapCreate(void);
void HashmapPut(Hashmap *map, const char *key, void *value, size_t size);
void *HashmapGet(Hashmap *map, const char *key);
u8 HashmapRemove(Hashmap *map, const char *key);
void *HashmapFree(Hashmap *map);

#endif  // _HASHMAP_H_

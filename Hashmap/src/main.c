#include "Hashmap.h"
#include <stdio.h>

struct Fruit {
  const char *name;
  float weight;
  float price;
};

static struct Fruit to_add[5] = {
  {"Apples", 1.5, 8.75},
  {"Blueberries", .25, 3.99},
  {"Watermellon", 5.0, 7.67},
  {"Oranges", 2.0, 5.99},
  {"Bananas", 1.79, 3.98}
};

void PrintFruitDetails(struct Fruit fruit) {
  printf("[Fruit]: %s | Weight: %f | Price: $%f\n", fruit.name, fruit.weight,
      fruit.price);
}

void PrintHashmapFruits(Hashmap *map) {
  struct Fruit *fruit;
  int i;
  for (i = 0; i < 5; ++i) {
    fruit = ((struct Fruit*) HashmapGet(map, to_add[i].name));
    if (!fruit) {
      printf("%s was not found in hashmap. skipping it.\n", to_add[i].name);
      continue;
    }
    PrintFruitDetails(*fruit);
  }


}

int main(void) {
  int i;
  Hashmap *map = HashmapCreate();
  struct Fruit newfruit = {"Oranges", 21.111, 45.99};
  for (i = 0; i < 5; ++i)
    HashmapPut(map, to_add[i].name, &to_add[i], sizeof(struct Fruit));
  PrintHashmapFruits(map);
  HashmapPut(map, "Oranges", &newfruit, sizeof(struct Fruit));
  HashmapRemove(map, "Blueberries");
  PrintHashmapFruits(map);
  map = HashmapFree(map);
  return 0;

}

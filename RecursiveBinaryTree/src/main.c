#include "BinaryTree.h"
#include <stdio.h>
#include <string.h>

typedef struct _Fruit {
  char name[32];
  float weight;
  float price;
  
} Fruit;

static Fruit fruits[5] = {
  {"Apples", 2.0, 8.99},
  {"Oranges", 3.0, 9.99},
  {"Apples", 4.0, 17.98},
  {"Banana", 1.0, 0.79},
  {"Bananas", 2.0, 1.58}
};


int CompareFruit(void *lhs, void *rhs) {
  Fruit *comparand; 
  Fruit *comparator;
  if (!lhs) {
    return -1;
  } else if (!rhs) {
    return 1;
  }
  comparand = ((Fruit*)lhs);
  comparator = ((Fruit*)rhs);
  if (comparand->price > comparator->price) {
    return 1;
  } else if (comparand->price < comparator->price) {
   return -1;
  } else {
    if (comparand->weight > comparand->weight)
      return 1;
    else if (comparand->weight < comparand->weight)
      return -1;
    else
      return strcmp(comparand->name, comparator->name);
  }
}

void PrintFruit(void *fruit) {
  Fruit *f;
  if (!fruit)
    return;
  f = ((Fruit*)fruit);
  printf("%s: Weight = %f | Price: $%f\n", f->name, f->weight, f->price);
}

int main(void) {
  int i;
  BinaryTree *tree = BinaryTreeCreate();
  for (i=0; i < 5; ++i)
    BinaryTreeAdd(tree, &fruits[i], sizeof(Fruit), CompareFruit);
  puts("-----------------------------------------");
  BinaryTreeInOrderPrint(tree, PrintFruit);
  BinaryTreeRemove(tree, &fruits[2], CompareFruit);
  puts("-----------------------------------------");
  BinaryTreeInOrderPrint(tree, PrintFruit);
  puts("-----------------------------------------");
  BinaryTreeFree(tree);

  return 0;
}

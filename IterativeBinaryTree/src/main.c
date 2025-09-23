#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>
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


int CompareFruit(const void *lhs, const void *rhs) {
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




static int blocks_opened = 0, blocks_closed = 0;

void *malloc_wrapped(size_t sz) {
  ++blocks_opened;
  return malloc(sz);
}
void free_wrapped(void *vp) {
  ++blocks_closed;
  free(vp);
}

static int cbo = 0, cbc = 0;

void *calloc_wrapped(size_t nm, size_t sz) {
  ++cbo;
  return calloc(nm, sz);
}

void free_callocs_wrapped(void *vp) {
  ++cbc;
  free(vp);
}

void InOrderPrint_FruitTree(BinaryTree_t *tree) {
  BinaryTreeNode_t *root;
  BinaryTreeNode_t **node_stack = calloc_wrapped(BinaryTree_Element_Count(tree)+1, sizeof(void*));
  bool *visited_flag_stack = calloc_wrapped(BinaryTree_Element_Count(tree)+1, sizeof(bool));
  int top = -1;
  node_stack[++top] = BinaryTree_Get_Root(tree);
  visited_flag_stack[top] = false;
  do {
    root = node_stack[top];
    if (NULL == root) {
      --top;
      continue;
    }
    if (visited_flag_stack[top]) {
      PrintFruit(root->data);
      visited_flag_stack[top] = false;
      node_stack[top] = root->r;
      continue;
    }
    visited_flag_stack[top] = true;

    node_stack[++top] = root->l;
    visited_flag_stack[top] = false;

  } while (-1 < top);
  free_callocs_wrapped(node_stack);
  free_callocs_wrapped(visited_flag_stack);
}

int main(void) {
  int i;
  BinaryTree_t *tree = BinaryTree_Create(malloc_wrapped, free_wrapped, NULL, NULL, CompareFruit, sizeof(Fruit));
  for (i=0; i < 5; ++i)
    BinaryTree_Insert(tree, &fruits[i]);
  puts("-----------------------------------------");
  InOrderPrint_FruitTree(tree);
  BinaryTree_Remove(tree, &fruits[2]);
  puts("-----------------------------------------");
  InOrderPrint_FruitTree(tree);
  puts("-----------------------------------------");
  BinaryTree_Destroy(tree);
  printf("\x1b[1mMalloc blocks opened:\t\t\x1b[34m%d\x1b[0m\n"
         "\x1b[1mMalloc blocks freed:\t\t\x1b[34m%d\x1b[0m\n"
         "\x1b[1mCalloc blocks opened:\t\t\x1b[34m%d\x1b[0m\n"
         "\x1b[1mCalloc blocks freed:\t\t\x1b[34m%d\x1b[0m\n",
         blocks_opened, blocks_closed, cbo, cbc);

  return 0;
}

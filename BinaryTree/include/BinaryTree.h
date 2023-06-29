#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include <stddef.h>
#include <stdint.h>

struct _BTNode {
  void* data;
  struct _BTNode *l, *r;
  int height;
};

typedef struct _BinaryTree {
 struct _BTNode *root;
} BinaryTree;





typedef int ComparisonCB(void*, void*);

BinaryTree *BinaryTreeCreate(void);
void BinaryTreeAdd(BinaryTree*, void*, size_t, ComparisonCB);
void BinaryTreeRemove(BinaryTree*, void*, ComparisonCB);
uint8_t BinaryTreeContains(BinaryTree*, void*, ComparisonCB);
void *BinaryTreeFetch(BinaryTree*, void*, ComparisonCB);
void *BinaryTreeFree(BinaryTree*);
void BinaryTreeInOrderPrint(BinaryTree*, void (print_callback(void*)));






#endif  /* _BINARY_TREE_H_ */

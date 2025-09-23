#include "BinaryTree.h"
#include <bits/stdint-uintn.h>
#include <stdlib.h>
#include <string.h>

typedef struct _BTNode BTNode;

BinaryTree *BinaryTreeCreate(void) {
  return (BinaryTree*)calloc(1, sizeof(BinaryTree));
}


static int Height(BTNode *node) {
  return !node ? -1 : node->height;
}

static void RecalcHeight(BTNode *node) {
  int lh,rh;
  if (!node) return;
  node->height = 
    (lh = Height(node->l)) > (rh = Height(node->r)) 
      ? (lh + 1) 
      : (rh + 1);
}

static int BalanceFact(BTNode *node) {
  return !node ? 0 : Height(node->l) - Height(node->r);
}

static BTNode * BTNodeLLRotate(BTNode *root) {
  BTNode *new_root = root->l;
  root->l = new_root->r;
  RecalcHeight(root);
  new_root->r = root;
  RecalcHeight(new_root);
  return new_root;
}

static BTNode *BTNodeLRRotate(BTNode *root) {
  BTNode *new_left = root->l->r;
  root->l->r = new_left->l;
  RecalcHeight(root->l);
  new_left->l = root->l;
  RecalcHeight(new_left);
  root->l = new_left;
  RecalcHeight(root);
  return BTNodeLLRotate(root);
}


static BTNode *BTNodeRRRotate(BTNode *root) {
  BTNode *new_root = root->r;
  root->r = new_root->l;
  RecalcHeight(root);
  new_root->l = root;
  RecalcHeight(new_root);
  return new_root;
}

static BTNode *BTNodeRLRotate(BTNode *root) {
  BTNode *new_right = root->r->l;
  root->r->l = new_right->r;
  RecalcHeight(root->r);
  new_right->r = root->r;
  RecalcHeight(new_right);
  root->r = new_right;
  RecalcHeight(root);
  return BTNodeRRRotate(root);
}



static BTNode *BTInternalAdd(BTNode *root, void *data, size_t size, 
    ComparisonCB cmp, uint8_t *rebal_flag) {
  int diff;
  if (!root) {
    root = (BTNode*)calloc(1, sizeof(BTNode));
    root->data = (void*)calloc(1, size);
    memcpy(root->data, data, size);
    *rebal_flag = 1;
    return root;  
  }
  diff = cmp(data, root->data);
  if (!diff) {
    /* Dupes verboden. Return early w/o adding anything. */
    rebal_flag = 0;
    return root;
  } else if (diff < 0) {
    root->l = BTInternalAdd(root->l, data, size, cmp, rebal_flag);
  } else {
    root->r = BTInternalAdd(root->r, data, size, cmp, rebal_flag);
  }

  if (!(*rebal_flag))
    return root;
  diff = BalanceFact(root);
  if (diff > 1) {
    if (cmp(data, root->l->data) < 0)
      root = BTNodeLLRotate(root);
    else
      root = BTNodeLRRotate(root);
  } else if (diff < -1) {
    if (cmp(data, root->r->data) > 0)
      root = BTNodeRRRotate(root);
    else
      root = BTNodeRLRotate(root);
  } else {
    RecalcHeight(root);
  }
  return root;
}


static BTNode *HibbardDelete(BTNode *root) {
  BTNode **stack = (BTNode**)calloc(root->r->height + 2, sizeof(void*));
  BTNode *tmp, *smallest = root->r;
  int bal, top = -1;
  while (smallest->l) {
    stack[++top] = smallest;
    smallest = smallest->l;
  }
  free(root->data);
  root->data = smallest->data;
  tmp = smallest;
  smallest = smallest->r;
  free(tmp);
  while (top > -1) {
    stack[top]->l = smallest;
    smallest = stack[top--];
    bal = BalanceFact(smallest);
    if (bal > 1) {
      if (BalanceFact(smallest->l) >= 0)
        smallest = BTNodeLLRotate(smallest);
      else
        smallest = BTNodeLRRotate(smallest);
    } else if (bal < -1) {
      if (BalanceFact(smallest->r) <= 0)
        smallest = BTNodeRRRotate(smallest);
      else
        smallest = BTNodeRLRotate(smallest);
    } else {
      RecalcHeight(smallest);
    }
  }
  root->r = smallest;
  bal = BalanceFact(root);
  if (bal > 1) {
    if (BalanceFact(root->l) >= 0)
      root = BTNodeLLRotate(root);
    else
      root = BTNodeLRRotate(root);
  } else if (bal < -1) {
    if (BalanceFact(root->r) <= 0)
      root = BTNodeRRRotate(root);
    else
      root = BTNodeRLRotate(root);
  } else {
    RecalcHeight(root);
  }
  return root;
}

static BTNode *BTInternalRm(BTNode *root, void *data, ComparisonCB cmp, 
    uint8_t *rebal_flag) {
  int diff;
  BTNode *tmp;
  if (!root) {
    *rebal_flag = 0;
    return root;
  }
  diff = cmp(data, root->data);
  if (diff < 0) {
    root->l = BTInternalRm(root->l, data, cmp, rebal_flag);
  } else if (diff > 0) {
    root->r = BTInternalRm(root->r, data, cmp, rebal_flag);
  } else {
    *rebal_flag = 1;
    if (!(root->l)) {
      tmp = root->r;
      free(root->data);
      free(root);
      return tmp;
    } else if (!(root->r)) {
      tmp = root->l;
      free(root->data);
      free(root);
      return tmp;
    }
    return HibbardDelete(root);
  }
  if (!(*rebal_flag))
    return root;
  
  diff = BalanceFact(root);
  if (diff > 1) {
    root = (BalanceFact(root->l) >= 0) 
      ? BTNodeLLRotate(root) : BTNodeLRRotate(root);
  } else if (diff < -1) {
    root = (BalanceFact(root->r) <= 0)
      ? BTNodeRRRotate(root) : BTNodeRLRotate(root);
  } else {
    RecalcHeight(root);
  }
  return root;
}




void BinaryTreeAdd(BinaryTree *tree, void *data, size_t size,
    ComparisonCB comparison_callback) {
  uint8_t flag = 0;
  if (!tree)
    return;
  tree->root = BTInternalAdd(tree->root, data, size, comparison_callback, &flag);
}
void BinaryTreeRemove(BinaryTree *tree, void *data, 
    ComparisonCB comparison_callback) {
  uint8_t flag = 0;
  if (!tree)
    return;
  tree->root = BTInternalRm(tree->root, data, comparison_callback, &flag);

}
uint8_t BinaryTreeContains(BinaryTree *tree, void *data, ComparisonCB cmp) {
  BTNode *root = tree->root;
  int diff;
  if (!tree)
    return 0;
  while (root) {
    diff = cmp(data, root->data);
    if (diff < 0) {
      root = root->l;
      continue;
    } else if (diff > 0) {
      root = root->r;
      continue;
    } else {
      return 1;
    }
  }
  return 0;
}
void *BinaryTreeFree(BinaryTree *tree) {
  BTNode **stack;
  BTNode *curr;
  int top = -1;
  if (!tree)
    return NULL;
  if (!(tree->root)) {
    free(tree);
    return NULL;
  }
  stack = (BTNode**)calloc((1<<(Height(tree->root)+1)) - 1, sizeof(void*));
  stack[++top] = tree->root;
  while (top > -1) {
    curr = stack[top--];
    if (curr->l)
      stack[++top] = curr->l;
    if (curr->r)
      stack[++top] = curr->r;
    free(curr->data);
    free(curr);
  }
  free(stack);
  free(tree);
  return NULL;
}

static void BTNodeInternalInOrderTraverse(BTNode *root, void pcb(void*)) {
  if (!root)
    return;
  BTNodeInternalInOrderTraverse(root->l, pcb);
  pcb(root->data);
  BTNodeInternalInOrderTraverse(root->r, pcb);
}


void BinaryTreeInOrderPrint(BinaryTree *tree, void print_callback(void*)) {
  if (!tree)
    return;
  BTNodeInternalInOrderTraverse(tree->root, print_callback);

  /* Will iteratively later :) for now, just recursive helper func bc im tired and its almost 4 am lol
   * 
   */
  /* BTNode **stack;
  BTNode *current;
  int top = -1;
  if (!tree)
    return;
  if (!tree->root)
    return;
  stack = (BTNode**)calloc((1<<(Height(tree->root) + 1)) - 1, sizeof(BTNode));
  stack[++top] = tree->root;
  while (top > -1) {
    
  } */
}

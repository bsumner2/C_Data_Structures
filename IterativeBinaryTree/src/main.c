#include "bstree.h"
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>






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

void InOrderPrint_IntTree(BinaryTree_t *tree) {
  BinaryTreeNode_t *root;
  BinaryTreeNode_t **node_stack = calloc_wrapped(BinaryTree_Element_Count(tree)+1, sizeof(void*));
  bool *visited_flag_stack = calloc_wrapped(BinaryTree_Element_Count(tree)+1, sizeof(bool));
  int top = -1;
  int idx = 0;
  node_stack[++top] = BinaryTree_Get_Root(tree);
  visited_flag_stack[top] = false;
  do {
    root = node_stack[top];
    if (NULL == root) {
      --top;
      continue;
    }
    if (visited_flag_stack[top]) {
      printf("\x1b[1;34mtree\x1b[0m<\x1b[1;33mInteger\x1b[0m>[\x1b[1;32m%d\x1b[0m] = \x1b[1;35m%d\x1b[0m\n", idx++, *(int*)root->data);
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
static int icmp(const void *a, const void *b) {
  return *(int*)a - *(int*)b;
}


bool InOrderValidate_IntTree(BinaryTree_t *tree, int *numlist, size_t nmemb) {
  size_t tree_nmemb = BinaryTree_Element_Count(tree);
  BinaryTreeNode_t *stack[tree_nmemb+1], *root = BinaryTree_Get_Root(tree);
  bool visit_stack[tree_nmemb+1];
  size_t  idx = 0;
  int top = -1;
  bool validation_passed = true;
  if ((const size_t)nmemb != tree_nmemb) {
    printf("Validation 1 failed. Nmemb expected (%lu) != nmemb of tree "
        "(%lu).\n", nmemb, tree_nmemb);
    validation_passed = false;
  }

  for (top = 0, stack[0] = root, visit_stack[0] = false
      ; -1 < top
      ; root = stack[top]) {
    if (NULL == root) {
      --top;
      continue;
    }
    if (visit_stack[top]) {
      if (0!=icmp(root->data, numlist+idx)) {
        printf("Validation 2 failed. tree[%lu]:=%d != numlist[%lu]:=%d\n", idx, *(int*)root->data, idx, numlist[idx]);
        validation_passed = false;
      }
      ++idx;
      stack[top] = root->r;
      visit_stack[top] = false;
      continue;
    }
    visit_stack[top] = true;
    stack[++top] = root->l;
    visit_stack[top] = false; 
  }
  if (idx!=nmemb) {
    printf("Validation 3 failed. Only traversed %lu nodes, when %lu were "
        "expected total.\n", idx, nmemb);
    validation_passed = false;
  }
  return validation_passed;
}

void PrintNumlist(int *numlist, size_t nmemb) {
  for (size_t i = 0; i < nmemb; ++i) {
    printf("\x1b[1;34mnumlist\x1b[0m[\x1b[1;32m%lu\x1b[0m] = \x1b[1;35m%d\x1b[0m\n", i, numlist[i]);
  }
}

int main(void) {
  srand(time(NULL));
  BinaryTree_t *tree = BinaryTree_Create(malloc_wrapped, free_wrapped, NULL, NULL, icmp, sizeof(int), NULL);
  int numlist[256], num, insert_count=0, fail_count=0;
  numlist[0] = INT_MAX&rand();
  for (int i = 1; i < 256; qsort(numlist, ++i, sizeof(int), icmp)) {
     do 
       num = INT_MAX&rand(); 
     while (NULL!=bsearch(&num, numlist, i, sizeof(int), icmp));
     numlist[i] = num;
  }
  
  for (int i = 0; i < 256; ++i) {
    num = numlist[i];
    printf("Inserting \x1b[1;34mnumlist\x1b[0m[\x1b[1;32m%d\x1b[0m] = "
        "\x1b[1;35m%d\x1b[0m into tree: ", i, num);
    if (!BinaryTree_Insert(tree, &num)) {
      ++fail_count;
      puts("\x1b[1;31mFAILED\x1b[0m");
    } else {
      ++insert_count;
      puts("\x1b[1;34mSUCCESS\x1b[0m");
    }
  }
  if (0!=fail_count) {
    printf("%d out of %d insertion attempts were successful.\n%d failed.\n"
        "Success + Fail counts = %d+%d = %d\n",
        insert_count, 256, fail_count, insert_count, fail_count, insert_count+fail_count);
    BinaryTree_Destroy(tree);
    printf("\x1b[1mMalloc blocks opened:\t\t\x1b[34m%d\x1b[0m\n"
           "\x1b[1mMalloc blocks freed:\t\t\x1b[34m%d\x1b[0m\n"
           "\x1b[1mCalloc blocks opened:\t\t\x1b[34m%d\x1b[0m\n"
           "\x1b[1mCalloc blocks freed:\t\t\x1b[34m%d\x1b[0m\n",
           blocks_opened, blocks_closed, cbo, cbc);
    return 0;
  }
  fail_count = 0, insert_count = 0;
  bool list[256];
  memset(list, 0x01010101, sizeof(list));
  
  for (int ct = 0, idx = rand()&255; BinaryTree_Element_Count(tree)!=0 && 256 > ct; idx = rand()&255) {
    if (!list[idx])
      continue;
    list[idx] = 0;
    ++ct;

    printf("Removing \x1b[1;34mnumlist\x1b[0m[\x1b[1;32m%d\x1b[0m] = "
        "\x1b[1;35m%d\x1b[0m from tree: ", idx, num);
    if (!BinaryTree_Remove(tree, numlist+idx)) {
      ++fail_count;
      puts("\x1b[1;31mFAILED\x1b[0m");
    } else {
      ++insert_count;
      puts("\x1b[1;34mSUCCESS\x1b[0m");
    }
  }
  if (0!=fail_count) {
    printf("%d out of %d removal attempts were successful.\n%d failed.\n"
        "Success + Fail counts = %d+%d = %d\n",
        insert_count, 256, fail_count, insert_count, fail_count, insert_count+fail_count);
    BinaryTree_Destroy(tree);
    printf("\x1b[1mMalloc blocks opened:\t\t\x1b[34m%d\x1b[0m\n"
           "\x1b[1mMalloc blocks freed:\t\t\x1b[34m%d\x1b[0m\n"
           "\x1b[1mCalloc blocks opened:\t\t\x1b[34m%d\x1b[0m\n"
           "\x1b[1mCalloc blocks freed:\t\t\x1b[34m%d\x1b[0m\n",
           blocks_opened, blocks_closed, cbo, cbc);
    return 0;
  }
  InOrderValidate_IntTree(tree, numlist, 256);
  puts("-----------------------------------------");
  InOrderPrint_IntTree(tree);
  PrintNumlist(numlist, 256);
  puts("-----------------------------------------");
  BinaryTree_Destroy(tree);
  printf("\x1b[1mMalloc blocks opened:\t\t\x1b[34m%d\x1b[0m\n"
         "\x1b[1mMalloc blocks freed:\t\t\x1b[34m%d\x1b[0m\n"
         "\x1b[1mCalloc blocks opened:\t\t\x1b[34m%d\x1b[0m\n"
         "\x1b[1mCalloc blocks freed:\t\t\x1b[34m%d\x1b[0m\n",
         blocks_opened, blocks_closed, cbo, cbc);

  return 0;
}

/* Written by: Burton O Sumner */
#ifndef BINARY_TREE
#define BINARY_TREE

typedef enum
{
    PRE, IN, POST
} PrintOrder;

typedef struct node
{
    int key;
    struct node *left, *right;
} Node;

typedef struct tree
{
    Node* root;
} BinaryTree;


void addToTree(int key, BinaryTree* tree);
Node* recursiveTreeAdd(int key, Node* node);

void removeFromTree(int key, BinaryTree* tree);
Node* recursiveTreeRemove(int key, Node* node);
Node* findMinimumInSubTree(Node* node);

void invertTree(BinaryTree* tree);
Node* recursiveTreeInversion(Node* node);


void removeAllGreaterThan(int key, BinaryTree* tree);
Node* recursivelyRemoveAllGreaterThan(int key, Node* node);

void deallocateTree(BinaryTree* tree);
Node* deallocationTraversal(Node* node);

unsigned char searchInTree(int key, BinaryTree tree);
Node* recursiveTreeSearch(int key, Node *node);


void printTree(BinaryTree tree, PrintOrder order);
void printInOrder(Node* node);
void printPreOrder(Node* node);
void printPostOrder(Node* node);

Node* newNode(int key);
#endif

/** Written by: Burton O Sumner */
#include<stdio.h>
#include<stdlib.h>
#include"../include/BinaryTree.h"

Node* newNode(int key)
{
    Node* ret = malloc(sizeof(Node));
    
    ret->key = key;
    ret->left = ret->right = NULL;

    return ret;
}

void addToTree(int key, BinaryTree* tree)
{   
    if(tree==NULL)
    {
        printf("Tree param is NULL. No values were added.\n");
        return;
    }
        tree->root = recursiveTreeAdd(key, tree->root);
}

Node* recursiveTreeAdd(int key, Node* node)
{
    if(node==NULL)
        node = newNode(key);
    else if(key==node->key)
        return node; //Return node without changing any children. Duplicates are not allowed.
    else if(key < node->key)
        node->left = recursiveTreeAdd(key, node->left);
    else
        node->right = recursiveTreeAdd(key, node->right);
    return node;
}

void removeFromTree(int key, BinaryTree* tree)
{
    if(tree==NULL)
    {
        printf("Tree param is NULL. No values were removed.\n");
        return;
    }
    tree->root = recursiveTreeRemove(key, tree->root);
}

Node* recursiveTreeRemove(int key, Node* node)
{
    if(node==NULL)
        return NULL;
    else if(key < node->key)
        node->left = recursiveTreeRemove(key, node->left);
    else if(key > node->key)
        node->right = recursiveTreeRemove(key, node->right);
    else
    {
        if(node->right==NULL)
        {
            Node* temp = node->left;
            free(node);
            return temp;
        }
        else if(node->left==NULL)
        {
            Node* temp = node->right;
            free(node);
            return temp;
        }
        else
        {
            Node* temp = findMinimumInSubTree(node->right);
            node->key = temp->key;
            node->right = recursiveTreeRemove(temp->key, node->right);
        }
    }
    return node;
}

Node* findMinimumInSubTree(Node* node)
{
    if(node==NULL) return NULL;
    if(node->left!=NULL)
        node = node->left;
    return node;
}

unsigned char searchInTree(int key, BinaryTree tree)
{
    return (recursiveTreeSearch(key, tree.root)!=NULL)?1:0;
}

Node* recursiveTreeSearch(int key, Node* node)
{
    if(node==NULL) return NULL;
    if(key < node->key)
        return recursiveTreeSearch(key, node->left);
    else if(key > node->key)
        return recursiveTreeSearch(key, node->right);
    else
        return node;
}

void invertTree(BinaryTree* tree)
{
    if(tree==NULL)
    {
        printf("Tree param NULL. No inversion occurred.\n");
        return;
    }
    tree->root = recursiveTreeInversion(tree->root);
}

Node* recursiveTreeInversion(Node* node)
{
    if(node==NULL) return NULL;
    Node* temp = node->left;
    node->left = recursiveTreeInversion(node->right);
    node->right = recursiveTreeInversion(temp);
    return node;
}



void printTree(BinaryTree tree, PrintOrder order)
{
    if(tree.root==NULL) return;
    switch(order)
    {
        case PRE:
            printPreOrder(tree.root);
            break;
        case IN:
            printInOrder(tree.root);
            break;
        case POST:
            printPostOrder(tree.root);
            break;
        default:
            printf("Invalid order param. No printing occurred.\n");
            return;
    }
}

void printPreOrder(Node* node)
{
    if(node==NULL) return;
    printf("%d\n", node->key);
    printPreOrder(node->left);
    printPreOrder(node->right);
}


void printInOrder(Node* node)
{
    if(node==NULL) return;
    
    printInOrder(node->left);
    printf("%d\n", node->key);
    printInOrder(node->right);
}

void printPostOrder(Node* node)
{
    if(node==NULL) return;
    printPostOrder(node->left);
    printPostOrder(node->right);
    printf("%d\n", node->key);
}

void deallocateTree(BinaryTree* tree)
{
    if(tree==NULL) return;
    tree->root = deallocationTraversal(tree->root);
}

Node* deallocationTraversal(Node* node)
{
    if(node==NULL) return NULL;
    node->left = deallocationTraversal(node->left);
    node->right = deallocationTraversal(node->right);
    free(node);
    return NULL;
}

void removeAllGreaterThan(int key, BinaryTree* tree)
{
    if(tree==NULL)
    {
        printf("Tree param is NULL, no removals occurred.\n");
        return;
    }
    tree->root = recursivelyRemoveAllGreaterThan(key, tree->root);
}

Node* recursivelyRemoveAllGreaterThan(int key, Node* node)
{
    if(node==NULL) return NULL;
    if(key >= node->key)
        node->right = recursivelyRemoveAllGreaterThan(key, node->right);
    else
    {
        Node* toDealloc = node;
        if(node->left!=NULL)
        {
            node->right = deallocationTraversal(node->right);
            node = recursivelyRemoveAllGreaterThan(key, node->left);
            free(toDealloc);
        }
        else
        {
            node->right = deallocationTraversal(node->right);
            node = NULL;
            free(toDealloc);
        }
    }
    return node;
    

}

int main()
{
    int heck[5] = {1, 6, 3, 4, 2};

    BinaryTree tree;
    tree.root = NULL;

    int i;
    for(i = 0; i < 5; i++)
    {
        printf("Adding %d to tree.\n", heck[i]);
        addToTree(heck[i], &tree);
    }

    printf("------------------------Tree populated. Printing in order\n");
    printTree(tree, IN);
    invertTree(&tree);
    printf("-------------------------------Tree inverted. Printing in order\n");
    printTree(tree, IN);
    printf("Reinverting tree for removal process.");
    invertTree(&tree);
    
    printf("Removing via removeFromTree function.");
    for(i = 0; i < 5; i++)
    {
        printf("Removing %d from tree.\n", heck[i]);
        removeFromTree(heck[i], &tree);
    }

    printf("--------------------------------------Removal complete. Printing in order to see if there are any stragglers.(should be empty)\n\n");

    printTree(tree, IN);

    printf("====================================================================================================================================\n\n");
    printf("--------------------Repopulating tree for new demo.\n");
    int heck2[10] = {25, 30, 12, 39, 4, 19, 50, 28, 100, -20};
    for(i = 0; i < 10; i++)
    {
        printf("Adding %d to the tree.\n", heck2[i]);
        addToTree(heck2[i], &tree);
    }
    printf("------------------------Tree populated. Printing in order\n");
    printTree(tree, IN);
    
    removeAllGreaterThan(27, &tree);


    printf("------------------------Removed all greater than %d. Printing graph in order.\n", 27);
    printTree(tree, IN);

    printf("------------------------Deallocating tree. Printing tree. (Should be empty if all goes according to plan\n");
    deallocateTree(&tree);
    printTree(tree, IN);

    return 0;

}

/** Written by Burton O Sumner */
#ifndef LINKED_LIST
#define LINKED_LIST



struct node
{
    int key;
    struct node *next;

};

typedef struct node Node;




typedef struct
{
    Node* head;
    Node* current;
    Node* previous;
} LinkedList;

/** @brief Constructs a new Linked List */

void add(int key, LinkedList* list);
void removeNode(int key, LinkedList* list);
void printList(LinkedList list);
Node* newNode(int key);








#endif

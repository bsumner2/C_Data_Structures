/** Written by Burton O Sumner */
#include <stdio.h>
#include <stdlib.h>
#include "../include/LinkedList.h"




void addNode(int key, LinkedList* list)
{
    if(list->head==NULL)
    {
        list->head = newNode(key);
        list->current = list->head;
        list->previous = NULL;
        return;
    }

    Node* cursor = list->head;
    while(cursor->next != NULL)
        cursor =  cursor->next;
    cursor->next = newNode(key);
    list->previous = cursor;
    list->current = cursor->next;
}

void removeNode(int key, LinkedList* list)
{

    if(list->head->key==key)
    {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }
    
    list->previous = list->head;
    list->current = list->head->next;
    while(list->current!=NULL)
    {
        if(list->current->key==key)
        {
            list->previous->next = list->current->next;
            free(list->current);
            list->current = list->previous->next;
            return;
        }

        list->previous = list->current;
        list->current = list->current->next;
    }


    
}

void deallocateList(LinkedList* list)
{
    list->previous = list->head;
    list->current = list->head;
    while(list->current!=NULL)
    {
        list->current = list->previous->next;
        free(list->previous);
        list->previous = list->current;
    }
}





Node* newNode(int key)
{
    Node* ret = calloc(1, sizeof(Node));
    ret->key = key;
    ret->next = NULL; 

    return ret;
}

void printList(LinkedList list)
{
    Node* cursor = list.head;
    while(cursor!=NULL)
    {
        printf("%d\n", cursor->key);
        cursor = cursor->next;
    }
    
}

int main()
{

    int heck[10] = {1,4 , 7, 4, 2, 5, 10, 2, 38, 49};
    LinkedList list;

    list.head = NULL;
    list.current = NULL;
    list.previous = NULL;


    int i;
    for(i=0;i<10; i++)
    {

        printf("Adding %d to the linked list\n", heck[i]);
        addNode(heck[i], &list);

    }

    printf("-------Nodes added.---------------Printing List from head to end-------------\n");
    printList(list);

    printf("Removing %d from the list.\n", 1);
    removeNode(1, &list);
    printf("Removing %d from the list.\n", 2);
    removeNode(2, &list);
    printf("Removing %d from the list.\n", 2);
    removeNode(2, &list);
    printList(list);
    printf("-------------------------Deallocating list and ending demo.");
    deallocateList(&list);
    return 0;
}

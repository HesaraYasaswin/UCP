#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void insertFirst(LinkedList* list, void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void deleteFirst(LinkedList* list) {
    if (list->head == NULL)
        return;

    Node* temp = list->head;
    list->head = list->head->next;
    free(temp->data);
    free(temp);
    list->size--;
}

void* getFirst(LinkedList* list) {
    if (list->head == NULL)
        return NULL;
    return list->head->data;
}

int isEmpty(LinkedList* list) {
    return list->size == 0;
}

void freeLinkedList(LinkedList* list) {
    Node* current = list->head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    free(list);
}








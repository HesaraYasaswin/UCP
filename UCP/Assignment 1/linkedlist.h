#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

typedef struct {
    int player_row;
    int player_col;
    int box_row;
    int box_col;
    int previous_pushrow;
    int previous_pushcol;
} Move;


LinkedList* createLinkedList();
void insertFirst(LinkedList* list, void* data);
void deleteFirst(LinkedList* list);
void* getFirst(LinkedList* list);
int isEmpty(LinkedList* list);
void freeLinkedList(LinkedList* list);

#endif /* LINKEDLIST_H */

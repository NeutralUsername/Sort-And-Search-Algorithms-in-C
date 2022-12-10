#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct Node *linkedListFromArray(int *array, int length) {
    struct Node *head = malloc(sizeof(struct Node));
    head->next = NULL;
    head->data = array[0];

    struct Node *tail = head;

    for (int i = 1; i < length; i++)
    {
        tail->next = malloc(sizeof(struct Node));
        tail = tail->next;
        tail->next = NULL;
        tail->data = array[i];
    }

    return head;
}

void printLinkedList(struct Node *head) {
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
}

void freeLinkedList(struct Node *head) {
    struct Node *next;
    while (head != NULL)
    {
        next = head->next;
        free(head);
        head = next;
    }
}
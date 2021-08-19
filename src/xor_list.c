#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "xor_list.h"
/*
 * #define XOR(a, b) (tList *)((unsigned int)(a)^(unsigned int)(b))
 *
 * Don't do that. It causes warning: "cast from pointer to integer of
 * different size".
 *
 * Sol: include <stdint.h> and use intptr_t to handle casting
 *
 */
#define XOR(a, b) (tList *)((intptr_t)(a)^(intptr_t)(b))

void insertHead(tList **head, int data)
{
    tList *newNode = malloc(sizeof(tList));
    newNode->val = data;

    if (*head == NULL) {
        newNode->link = NULL;
    } else {
        /* Update original link of head node */
        (*head)->link = XOR((*head)->link, newNode);
        newNode->link = *head;
    }
    *head = newNode;
}

void deleteHead(tList **head)
{
    if (!(*head))
        return;

    tList *tmp = (*head)->link;
    /* Update the link of new head */
    if (tmp)
        tmp->link = XOR((*head), tmp->link);
    free(*head);
    *head = tmp;
}

void printXorList(tList *head)
{
    if (!head)
        return;

    tList *prev = NULL;
    while (head) {
        tList *tmp = head;
        printf("%d ", head->val);
        head = XOR(prev, head->link);
        prev = tmp;
    }
    printf("\n");
}

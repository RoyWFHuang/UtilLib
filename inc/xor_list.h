#ifndef __xor_list_H__
#define __xor_list_H__


typedef struct _tList
{
    int val;
    struct _tList *link;
} tList;

void insertHead(tList **head, int data);
void deleteHead(tList **head);
void printXorList(tList *head);


#endif


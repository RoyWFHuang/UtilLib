#include <stdio.h>
#include "xor_list.h"

int main(){
    printf("start testing xor list.....\n");
    tList *list = NULL;
    for (int i = 0 ;i < 10; i++)
        insertHead(&list, i);
    printXorList(list);
    deleteHead(&list);
    printXorList(list);
    deleteHead(&list);
    printXorList(list);
    for (int i = 0 ;i < 8; i++)
        deleteHead(&list);
    return 0;
}
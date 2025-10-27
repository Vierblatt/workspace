#include <stdio.h>
#include "RBTree_Hash.h"

int main(void) {
    HashTable ht;
    InitHashTable(&ht, 8);

    InsertHash(&ht, 10, 100);
    InsertHash(&ht, 18, 180);
    InsertHash(&ht, 26, 260);
    InsertHash(&ht, 2, 20);
    InsertHash(&ht, -6, -60);
    InsertHash(&ht, 3, 30);

    printf("Initial table:\n");
    DisplayHash(&ht);

    int v;
    if (SearchHash(&ht, 18, &v)) printf("Found 18 -> %d\n", v);
    else printf("18 not found\n");

    if (SearchHash(&ht, 3, &v)) printf("Found 3 -> %d\n", v);
    else printf("3 not found\n");

    DeleteHash(&ht, 18);
    printf("After deleting 18:\n");
    DisplayHash(&ht);

    printf("Count = %d\n", GetCount(&ht));

    DestroyHashTable(&ht);
    return 0;
}


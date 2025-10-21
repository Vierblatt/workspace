#include "hash_map_chaining.h"
#include <stdlib.h>
#include <stdio.h>

static int hash_func(int key, int capacity) {
    return (key % capacity + capacity) % capacity;
}

static void hash_table_extend(HashTable* ht) {
    int old_capacity = ht->capacity;
    int new_capacity = old_capacity * EXTEND_RATIO;
    HashNode** new_table = (HashNode**)malloc(sizeof(HashNode*) * new_capacity);
    for (int i = 0; i < new_capacity; ++i) new_table[i] = NULL;
    // 重新分配所有节点
    for (int i = 0; i < old_capacity; ++i) {
        HashNode* curr = ht->table[i];
        while (curr) {
            HashNode* next = curr->next;
            int idx = hash_func(curr->key, new_capacity);
            curr->next = new_table[idx];
            new_table[idx] = curr;
            curr = next;
        }
    }
    free(ht->table);
    ht->table = new_table;
    ht->capacity = new_capacity;
}

void hash_table_init(HashTable* ht) {
    ht->capacity = INIT_TABLE_SIZE;
    ht->size = 0;
    ht->table = (HashNode**)malloc(sizeof(HashNode*) * ht->capacity);
    for (int i = 0; i < ht->capacity; ++i) ht->table[i] = NULL;
}

void hash_table_destroy(HashTable* ht) {
    for (int i = 0; i < ht->capacity; ++i) {
        HashNode* curr = ht->table[i];
        while (curr) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(ht->table);
    ht->table = NULL;
    ht->capacity = 0;
    ht->size = 0;
}

void hash_table_insert(HashTable* ht, int key, int value) {
    if ((double)(ht->size + 1) / ht->capacity > LOAD_FACTOR_THRESHOLD) {
        hash_table_extend(ht);
    }
    int idx = hash_func(key, ht->capacity);
    HashNode* curr = ht->table[idx];
    while (curr) {
        if (curr->key == key) {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    node->next = ht->table[idx];
    ht->table[idx] = node;
    ht->size++;
}

int hash_table_find(HashTable* ht, int key, int* value) {
    int idx = hash_func(key, ht->capacity);
    HashNode* curr = ht->table[idx];
    while (curr) {
        if (curr->key == key) {
            if (value) *value = curr->value;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

int hash_table_remove(HashTable* ht, int key) {
    int idx = hash_func(key, ht->capacity);
    HashNode* curr = ht->table[idx];
    HashNode* prev = NULL;
    while (curr) {
        if (curr->key == key) {
            if (prev) prev->next = curr->next;
            else ht->table[idx] = curr->next;
            free(curr);
            ht->size--;
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    return 0;
}

void hash_table_print(HashTable* ht) {
    printf("HashTable (capacity=%d, size=%d):\n", ht->capacity, ht->size);
    for (int i = 0; i < ht->capacity; ++i) {
        printf("[%d]:", i);
        HashNode* curr = ht->table[i];
        while (curr) {
            printf(" (%d->%d)", curr->key, curr->value);
            curr = curr->next;
        }
        printf("\n");
    }
}

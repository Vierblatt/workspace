#ifndef HASH_MAP_CHAINING_H
#define HASH_MAP_CHAINING_H

#define INIT_TABLE_SIZE 4
#define LOAD_FACTOR_THRESHOLD 0.75
#define EXTEND_RATIO 2

// 链表节点
typedef struct HashNode {
    int key;
    int value;
    struct HashNode* next;
} HashNode;

// 哈希表
typedef struct HashTable {
    HashNode** table;
    int capacity;
    int size;
} HashTable;

void hash_table_init(HashTable* ht);
void hash_table_destroy(HashTable* ht);
void hash_table_insert(HashTable* ht, int key, int value);
int hash_table_find(HashTable* ht, int key, int* value);
int hash_table_remove(HashTable* ht, int key);
void hash_table_print(HashTable* ht);

#endif // HASH_MAP_CHAINING_H

#ifndef HASH_TABLE_RBT_H
#define HASH_TABLE_RBT_H

#define OK 1
#define ERROR 0

typedef int Status;

/* 红黑树节点颜色 */
#define RED 1
#define BLACK 0

typedef struct RBNode {
    int key;
    int value;
    int color; /* RED or BLACK */
    struct RBNode *left, *right, *parent;
} RBNode;

/* 哈希表结构：动态数组的桶，每个桶为一棵红黑树的根指针 */
typedef struct HashTable {
    RBNode **buckets; /* 指向根节点指针数组，根节点使用全局 NIL 作为空 */
    int size;   /* 桶数量 */
    int count;  /* 键值对总数 */
} HashTable;

/* ADT 操作 */
void InitHashTable(HashTable *ht, int size);
void DestroyHashTable(HashTable *ht);
Status InsertHash(HashTable *ht, int key, int value);
Status SearchHash(HashTable *ht, int key, int *value);
Status DeleteHash(HashTable *ht, int key);
int GetCount(HashTable *ht);
void DisplayHash(HashTable *ht);

#endif /* HASH_TABLE_RBT_H */

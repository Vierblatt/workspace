#include "hash_table_rbt.h"
#include <stdlib.h>
#include <string.h>

/* 全局 NIL 节点，简化空指针处理 */
static RBNode _NIL_NODE;
static RBNode *NIL = NULL;

static void init_nil() {
    if (NIL) return;
    NIL = &_NIL_NODE;
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NULL;
}

/* Helper: create node */
static RBNode *rbnode_create(int key, int value) {
    RBNode *node = (RBNode *)malloc(sizeof(RBNode));
    if (!node) return NULL;
    node->key = key;
    node->value = value;
    node->color = RED;
    node->left = node->right = node->parent = NIL;
    return node;
}

/* Left rotate x: assume x->right != NIL */
static void left_rotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

/* Right rotate x: assume x->left != NIL */
static void right_rotate(RBNode **root, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != NIL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NIL) {
        *root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

/* Insert fixup */
static void insert_fixup(RBNode **root, RBNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(root, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

/* RB tree insert (standard) */
static RBNode *rb_insert_node(RBNode **root, int key, int value, int *inserted_new) {
    RBNode *y = NIL;
    RBNode *x = *root;
    while (x != NIL) {
        y = x;
        if (key == x->key) {
            x->value = value; /* update */
            if (inserted_new) *inserted_new = 0;
            return x;
        } else if (key < x->key) x = x->left;
        else x = x->right;
    }
    RBNode *z = rbnode_create(key, value);
    if (!z) return NULL;
    z->parent = y;
    if (y == NIL) {
        *root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    if (inserted_new) *inserted_new = 1;
    insert_fixup(root, z);
    return z;
}

/* Transplant for delete */
static void rb_transplant(RBNode **root, RBNode *u, RBNode *v) {
    if (u->parent == NIL) *root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

/* Tree minimum */
static RBNode *rb_minimum(RBNode *x) {
    while (x->left != NIL) x = x->left;
    return x;
}

/* Delete fixup */
static void delete_fixup(RBNode **root, RBNode *x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(root, x->parent);
                x = *root;
            }
        } else {
            RBNode *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

/* RB tree delete */
static int rb_delete_node(RBNode **root, int key) {
    RBNode *z = *root;
    while (z != NIL && z->key != key) {
        if (key < z->key) z = z->left;
        else z = z->right;
    }
    if (z == NIL) return 0; /* not found */
    RBNode *y = z;
    int y_original_color = y->color;
    RBNode *x;
    if (z->left == NIL) {
        x = z->right;
        rb_transplant(root, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        rb_transplant(root, z, z->left);
    } else {
        y = rb_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rb_transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_original_color == BLACK) delete_fixup(root, x);
    return 1;
}

/* Search node */
static RBNode *rb_search(RBNode *root, int key) {
    while (root != NIL && root->key != key) {
        if (key < root->key) root = root->left;
        else root = root->right;
    }
    return (root == NIL) ? NULL : root;
}

/* Inorder print */
static void rb_inorder_print(RBNode *root) {
    if (root == NIL) return;
    rb_inorder_print(root->left);
    printf("(%d,%d) ", root->key, root->value);
    rb_inorder_print(root->right);
}

/* Free all nodes */
static void rb_free_all(RBNode *root) {
    if (root == NIL) return;
    rb_free_all(root->left);
    rb_free_all(root->right);
    free(root);
}

/* Hash function: simple modulo */
static int hash_func(HashTable *ht, int key) {
    int idx = key % ht->size;
    if (idx < 0) idx += ht->size;
    return idx;
}

/* ADT implementations */
void InitHashTable(HashTable *ht, int size) {
    if (size <= 0) size = 8;
    init_nil();
    ht->size = size;
    ht->count = 0;
    ht->buckets = (RBNode **)malloc(sizeof(RBNode *) * size);
    for (int i = 0; i < size; i++) ht->buckets[i] = NIL;
}

void DestroyHashTable(HashTable *ht) {
    if (!ht || !ht->buckets) return;
    for (int i = 0; i < ht->size; i++) {
        if (ht->buckets[i] != NIL) rb_free_all(ht->buckets[i]);
    }
    free(ht->buckets);
    ht->buckets = NULL;
    ht->size = 0;
    ht->count = 0;
}

Status InsertHash(HashTable *ht, int key, int value) {
    if (!ht || !ht->buckets) return ERROR;
    int idx = hash_func(ht, key);
    int inserted_new = 0;
    RBNode *root = ht->buckets[idx];
    RBNode *ret = rb_insert_node(&root, key, value, &inserted_new);
    if (!ret) return ERROR;
    ht->buckets[idx] = root;
    if (inserted_new) ht->count++;
    return OK;
}

Status SearchHash(HashTable *ht, int key, int *value) {
    if (!ht || !ht->buckets) return ERROR;
    int idx = hash_func(ht, key);
    RBNode *node = rb_search(ht->buckets[idx], key);
    if (!node) return ERROR;
    if (value) *value = node->value;
    return OK;
}

Status DeleteHash(HashTable *ht, int key) {
    if (!ht || !ht->buckets) return ERROR;
    int idx = hash_func(ht, key);
    int ok = rb_delete_node(&ht->buckets[idx], key);
    if (ok) ht->count--;
    return ok ? OK : ERROR;
}

int GetCount(HashTable *ht) {
    if (!ht) return 0;
    return ht->count;
}

void DisplayHash(HashTable *ht) {
    if (!ht || !ht->buckets) return;
    for (int i = 0; i < ht->size; i++) {
        printf("Bucket %d: ", i);
        if (ht->buckets[i] == NIL) {
            printf("(empty)\n");
        } else {
            rb_inorder_print(ht->buckets[i]);
            printf("\n");
        }
    }
}


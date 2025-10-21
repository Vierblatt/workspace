#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <stdbool.h>

// 链队列结点类型
typedef struct QNode {
    int data;
    struct QNode *next;
} QNode;

// 链队列类型（带头结点）
typedef struct {
    QNode *front; // 指向头结点
    QNode *rear;  // 指向队尾结点
} LinkQueue;

// 初始化队列
void InitQueue(LinkQueue *q);
// 判空
bool QueueEmpty(LinkQueue *q);
// 入队
bool EnQueue(LinkQueue *q, int x);
// 出队
bool DeQueue(LinkQueue *q, int *x);
// 销毁队列
void DestroyQueue(LinkQueue *q);

#endif // LINKQUEUE_H


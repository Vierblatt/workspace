// 头文件：链队列类型和接口定义
#ifndef LINKQUEUE_H
#define LINKQUEUE_H
#include <stdbool.h>
typedef struct QNode {
    int data;
    struct QNode *next;
} QNode;
typedef struct {
    QNode *front;
    QNode *rear;
} LinkQueue;
void InitQueue(LinkQueue *q);
bool QueueEmpty(LinkQueue *q);
bool EnQueue(LinkQueue *q, int x);
bool DeQueue(LinkQueue *q, int *x);
void DestroyQueue(LinkQueue *q);
#endif


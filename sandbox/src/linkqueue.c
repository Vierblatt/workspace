#include "linkqueue.h"
#include <stdio.h>
#include <stdlib.h>

void InitQueue(LinkQueue *q) {
    q->front = q->rear = (QNode *)malloc(sizeof(QNode));
    if (!q->front) exit(1);
    q->front->next = NULL;
}

bool QueueEmpty(LinkQueue *q) {
    return q->front == q->rear;
}

bool EnQueue(LinkQueue *q, int x) {
    QNode *node = (QNode *)malloc(sizeof(QNode));
    if (!node) return false;
    node->data = x;
    node->next = NULL;
    q->rear->next = node;
    q->rear = node;
    return true;
}

bool DeQueue(LinkQueue *q, int *x) {
    if (QueueEmpty(q)) return false;
    QNode *p = q->front->next;
    *x = p->data;
    q->front->next = p->next;
    if (q->rear == p) q->rear = q->front;
    free(p);
    return true;
}

void DestroyQueue(LinkQueue *q) {
    QNode *p = q->front;
    while (p) {
        QNode *tmp = p;
        p = p->next;
        free(tmp);
    }
    q->front = q->rear = NULL;
}


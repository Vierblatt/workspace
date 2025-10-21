// 测试主函数
#include <windows.h>
#include <stdio.h>
#include "linkqueue.h"
int main() {
    system("chcp 65001");
    LinkQueue q;
    InitQueue(&q);
    printf("入队: 1, 2, 3\n");
    EnQueue(&q, 1);
    EnQueue(&q, 2);
    EnQueue(&q, 3);
    int x;
    printf("出队: ");
    while (!QueueEmpty(&q)) {
        DeQueue(&q, &x);
        printf("%d ", x);
    }
    printf("\n");
    DestroyQueue(&q);
    return 0;
}

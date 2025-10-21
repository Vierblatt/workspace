#include <stdio.h>

void assign_element(int S[], int n, int i, int e) {
    if (i >= 0 && i < n) {
        S[i] = e;
    } else {
        printf("索引越界！\n");
    }
}

int main() {
    int S[] = {1, 2, 3, 4, 5};
    int n = sizeof(S) / sizeof(S[0]);
    int i = 2;
    int e = 99;

    printf("原始序列: ");
    for (int j = 0; j < n; ++j) printf("%d ", S[j]);
    printf("\n");

    assign_element(S, n, i, e);

    printf("赋值后序列: ");
    for (int j = 0; j < n; ++j) printf("%d ", S[j]);
    printf("\n");

    printf("按回车键退出...");
    getchar();
    return 0;
}

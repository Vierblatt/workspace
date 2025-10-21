#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../sort.h"

void print_array(int arr[], int n) {
    for (int i = 0; i < n; ++i) printf("%d ", arr[i]);
    printf("\n");
}

void test_sort(void (*sort_func)(int[], int), int arr[], int n, const char* name, int print) {
    int* arr_tmp = (int*)malloc(n * sizeof(int));
    if (!arr_tmp) {
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; ++i) arr_tmp[i] = arr[i];
    if (print) {
        printf("排序前: ");
        print_array(arr_tmp, n);
    }
    clock_t start = clock();
    sort_func(arr_tmp, n);
    clock_t end = clock();
    if (print) {
        printf("排序后: ");
        print_array(arr_tmp, n);
    }
    printf("【%s】耗时：%.6f 秒\n", name, (double)(end - start) / CLOCKS_PER_SEC);
    free(arr_tmp);
}

int main() {
    // 仅在 Windows 下设置控制台为 UTF-8
    system("chcp 65001 > nul");
    srand((unsigned)time(NULL)); // 随机数种子只设置一次
    int sizes[] = {10, 100, 1000, 10000};
    const char* sort_names[] = {"选择排序", "冒泡排序", "优化冒泡排序"};
    void (*sort_funcs[])(int[], int) = {selection_sort, bubble_sort, bubble_sort_optimized};
    for (int s = 0; s < 4; ++s) {
        int n = sizes[s];
        int* arr = (int*)malloc(n * sizeof(int));
        if (!arr) {
            fprintf(stderr, "内存分配失败\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < n; ++i) arr[i] = rand() % 10000;
        printf("\n元素数量：%d\n", n);
        for (int i = 0; i < 3; ++i) {
            test_sort(sort_funcs[i], arr, n, sort_names[i], n <= 10);
        }
        free(arr);
    }
    printf("\n按回车键退出...");
    fflush(stdin); // 避免 getchar() 读取到残留字符
    getchar();
    return 0;
}

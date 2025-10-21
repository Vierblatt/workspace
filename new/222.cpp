// Fig. 6.19: fig06_19.c
// Binary search of a sorted array.
#include <stdio.h>
#define SIZE 15

// 递归的折半查找函数
int binarySearch(const int b[], int searchKey, int low, int high) {
    if (low > high) return -1; // 查找键不存在

    int middle = (low + high) / 2;

    if (searchKey == b[middle]) return middle;
    else if (searchKey < b[middle]) return binarySearch(b, searchKey, low, middle - 1);
    else return binarySearch(b, searchKey, middle + 1, high);
}

// 打印表头的函数
void printHeader(void) {
    puts("Indx:");
    for (int i = 0; i < SIZE; ++i) {
        printf("%3d ", i);
    }
    puts("");
    for (int i = 0; i < SIZE; ++i) {
        printf("--- ");
    }
    puts("");
}

// 打印数组元素的函数
void printRow(const int b[], int low, int mid, int high) {
    for (int i = 0; i < SIZE; ++i) {
        if (i < low || i > high) printf("   ");
        else if (i == mid) printf("%3d*", b[i]);
        else printf("%3d ", b[i]);
    }
    printf("\n");
}

int main(void) {
    int a[SIZE];

    // 创建数据
    for (int i = 0; i < SIZE; ++i) {
        a[i] = 2 * i + 1;
    }

    printHeader();
    printRow(a, 0, 0, SIZE - 1);

    int key;
    printf("Enter a number between 0 and 28: ");
    scanf("%d", &key);

    int result = binarySearch(a, key, 0, SIZE - 1);

    if (result!= -1) {
        printf("\n%d found at index %d\n", key, result);
    } else {
        printf("\n%d not found\n", key);
    }

    return 0;
}
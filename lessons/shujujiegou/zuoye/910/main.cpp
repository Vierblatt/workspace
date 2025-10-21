#include "SeqStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main() {
    // 设置控制台代码页为UTF-8，解决中文乱码问题
    SetConsoleOutputCP(CP_UTF8);
    
    // 测试数值转换功能
    int num;
    printf("===== 数值转换测试（十进制转八进制） =====\n");
    printf("请输入一个十进制整数：");
    scanf("%d", &num);
    printf("%d 转换为八进制是：", num);
    conversion(num);
    printf("\n");

    // 测试括号匹配功能
    char exp[100];
    printf("\n===== 括号匹配测试 =====\n");
    printf("请输入包含括号的表达式：");
    scanf("%s", exp);

    if (bracketMatching(exp)) {
        printf("括号匹配成功！\n");
    } else {
        printf("括号匹配失败！\n");
    }

    return 0;
}
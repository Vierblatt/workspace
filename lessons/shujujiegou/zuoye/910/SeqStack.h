#ifndef SEQSTACK_H
#define SEQSTACK_H

#include <stdio.h>
#include <stdlib.h>

// 状态码定义
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;

// 栈元素类型定义，改回char以支持括号匹配
typedef char SElemType;

// 顺序栈结构体定义
typedef struct {
    SElemType *base;  // 栈底指针
    SElemType *top;   // 栈顶指针
    int stacksize;    // 当前已分配的存储空间，以元素为单位
} SqStack;

// 顺序栈的基本操作函数声明

// 初始化栈
Status InitStack(SqStack *S);

// 销毁栈
Status DestroyStack(SqStack *S);

// 清空栈
Status ClearStack(SqStack *S);

// 判断栈是否为空
Status StackEmpty(SqStack S);

// 获取栈的长度
int StackLength(SqStack S);

// 获取栈顶元素
Status GetTop(SqStack S, SElemType *e);

// 入栈
Status Push(SqStack *S, SElemType e);

// 出栈
Status Pop(SqStack *S, SElemType *e);

// 数值转换：将十进制数转换为八进制数并输出
void conversion(int num);

// 括号匹配：判断表达式中的括号是否匹配
Status bracketMatching(char exp[]);

#endif // SEQSTACK_H
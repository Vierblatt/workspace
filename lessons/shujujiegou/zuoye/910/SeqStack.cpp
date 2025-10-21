#include "SeqStack.h"

// 初始化栈
Status InitStack(SqStack *S) {
    // 分配初始存储空间
    S->base = (SElemType *)malloc(100 * sizeof(SElemType));
    if (!S->base) {
        return OVERFLOW;  // 存储分配失败
    }
    S->top = S->base;    // 栈顶指针等于栈底指针，表示空栈
    S->stacksize = 100;  // 栈的初始容量
    return OK;
}

// 销毁栈
Status DestroyStack(SqStack *S) {
    free(S->base);
    S->base = NULL;
    S->top = NULL;
    S->stacksize = 0;
    return OK;
}

// 清空栈
Status ClearStack(SqStack *S) {
    S->top = S->base;  // 使栈顶指针重新指向栈底
    return OK;
}

// 判断栈是否为空
Status StackEmpty(SqStack S) {
    if (S.top == S.base)  // 栈顶指针等于栈底指针，表示空栈
        return OK;
    else
        return ERROR;
}

// 获取栈的长度
int StackLength(SqStack S) {
    return (S.top - S.base);  // 栈顶指针与栈底指针的差值即为栈的长度
}

// 获取栈顶元素
Status GetTop(SqStack S, SElemType *e) {
    if (S.top == S.base)  // 栈为空
        return ERROR;
    *e = *(S.top - 1);  // 栈顶指针指向栈顶元素的下一个位置，所以要减1
    return OK;
}

// 入栈
Status Push(SqStack *S, SElemType e) {
    // 判断栈是否已满
    if (S->top - S->base >= S->stacksize) {
        // 追加存储空间
        S->base = (SElemType *)realloc(S->base, (S->stacksize + 10) * sizeof(SElemType));
        if (!S->base) {
            return OVERFLOW;  // 存储分配失败
        }
        S->top = S->base + S->stacksize;  // 重新定位栈顶指针
        S->stacksize += 10;              // 增加存储容量
    }
    *S->top++ = e;  // 插入元素并向上移动栈顶指针
    return OK;
}

// 出栈
Status Pop(SqStack *S, SElemType *e) {
    if (S->top == S->base)  // 栈为空
        return ERROR;
    *e = *--S->top;  // 向下移动栈顶指针并取出元素
    return OK;
}

// 数值转换：将十进制数转换为八进制数并输出
void conversion(int num) {
    SqStack S;
    char e;  // 这里使用char类型
    InitStack(&S);  // 初始化栈

    // 将十进制数不断除以8，余数入栈
    while (num) {
        Push(&S, num % 8 + '0');  // 转换为字符存储
        num = num / 8;
    }

    // 将栈中元素依次出栈并输出，即为转换后的八进制数
    while (!StackEmpty(S)) {
        Pop(&S, &e);
        printf("%c", e);
    }

    DestroyStack(&S);  // 销毁栈
}

// 括号匹配：判断表达式中的括号是否匹配
Status bracketMatching(char exp[]) {
    SqStack S;
    int i = 0;
    char e;
    InitStack(&S);  // 初始化栈

    // 遍历表达式中的每个字符
    while (exp[i] != '\0') {
        switch (exp[i]) {
            case '(':
            case '[':
            case '{':
                Push(&S, exp[i]);  // 遇到左括号，入栈
                break;
            case ')':
                if (StackEmpty(S))  // 遇到右括号且栈为空，说明不匹配
                    return ERROR;
                GetTop(S, &e);
                if (e != '(')  // 遇到右括号且栈顶元素不为对应的左括号，说明不匹配
                    return ERROR;
                Pop(&S, &e);  // 匹配成功，出栈
                break;
            case ']':
                if (StackEmpty(S))
                    return ERROR;
                GetTop(S, &e);
                if (e != '[')
                    return ERROR;
                Pop(&S, &e);
                break;
            case '}':
                if (StackEmpty(S))
                    return ERROR;
                GetTop(S, &e);
                if (e != '{')
                    return ERROR;
                Pop(&S, &e);
                break;
        }
        i++;
    }

    // 若栈为空，说明所有括号都匹配；否则，说明有未匹配的左括号
    if (StackEmpty(S))
        return OK;
    else
        return ERROR;
}
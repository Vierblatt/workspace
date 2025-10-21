#include <stdio.h>
#include <stdbool.h>
#define MAX 100

void getCommands(int commands[][2]);
int turnRight(int d);
int turnLeft(int d);
void movePen(bool down, int a[][50], int *x, int *y, int dir, int dist);
void printArray(int a[][50]);

int main(void) {
    int commandArray[MAX][2] = {0};
    getCommands(commandArray);
    int count = 0;
    int floor[50][50] = {0};
    bool penDown = false;
    int direction = 0;
    int distance;
    int x = 0, y = 0;

    while (count < MAX && commandArray[count][0] != 9) {
        int command = commandArray[count][0];

        switch(command) {
            case 1: // 笔向上
                penDown = false;
                break;
            case 2: // 笔向下
                penDown = true;
                break;
            case 3: // 向右转
                direction = turnRight(direction);
                break;
            case 4: // 向左转
                direction = turnLeft(direction);
                break;
            case 5: // 前进
                if (scanf("%d", &distance) != 1 || distance <= 0) {
                    printf("错误：请输入一个正整数作为前进距离。\n");
                    while(getchar() != '\n'); // 清除无效输入
                    continue; // 跳过当前循环迭代
                }
                movePen(penDown, floor, &x, &y, direction, distance);
                printf("已前进%d单位。\n", distance);
                break;
            case 6: // 打印地板
                printArray(floor);
                break;         
        }
        count++;
    }
    return 0;
}

void getCommands(int commands[][2]) {
    int i = 0;
    int command;
    while (i < MAX) {
        if (scanf("%d", &command) != 1) { // 错误处理：检查输入有效性
            printf("输入错误，请输入数字。\n");
            while(getchar() != '\n'); // 清除无效输入
            continue; // 继续请求输入
        }
        if (command == 9) {
            break;
        }
        commands[i][0] = command;
        if (command == 5) { // 只有在命令是前进时才请求距离
            if (scanf("%d", &commands[i][1]) != 1) { // 错误处理：检查输入有效性
                printf("输入错误，请输入数字。\n");
                while(getchar() != '\n'); // 清除无效输入
                continue; // 继续请求输入
            }
        }
        i++;
    }
}

int turnRight(int d) {
    return (d + 1) % 4;
}

int turnLeft(int d) {
    return (d + 3) % 4;
}

void movePen(bool down, int a[][50], int *x, int *y, int dir, int dist) {
    for (int i = 0; i < dist; i++) {
        switch (dir) {
            case 0: (*y)--; break; // 向上
            case 1: (*x)++; break; // 向右
            case 2: (*y)++; break; // 向下
            case 3: (*x)--; break; // 向左
        }

        // 检查边界和绘画状态
        if (*x >= 0 && *x < 50 && *y >= 0 && *y < 50 && down) {
            a[*x][*y] = 1; // 只有在笔下时才能绘图
        } else {
            break; // 超出边界则停止移动
        }
    }
}

void printArray(int a[][50]) {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            printf("%c", a[i][j] ? '*' : ' ');
        }
        printf("\n");
    }
}

#include <stdio.h>
#include <stdbool.h>
#define MAX 100

// 申明函数
void getCommands(int commands[][2]);// 读取命令并存入数组
int turnRight(int d);// 向右转
int turnLeft(int d);// 向左转
void movePen(bool down, int a[][50], int *x, int *y, int dir, int dist);// 移动笔
void printArray(int a[][50]);// 打印地板

int main(void) {
    int commandArray[MAX][2] = {0};
    getCommands(commandArray);
    int count = 0;
    int floor[50][50] = {0};
    bool penDown = false;
    int direction = 0;
    int distance;
    int x = 0, y = 0;

    while (count < MAX && commandArray[count][0]!= 9) {
        int command = commandArray[count][0];
        // 错误处理：检查命令有效性
        if (command < 1 || command > 6) {
            count++;
            continue; // 跳过当前循环，继续到下一个
        }
        switch (command) {
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
                distance = commandArray[count][1];
                movePen(penDown, floor, &x, &y, direction, distance);
                break;
            case 6: // 打印地板
                printArray(floor);
                break;
        }
        count++;
    }
    return 0;
}

// 读取命令并存入数组模块
void getCommands(int commands[][2]) {
    int i = 0;
    int command;
    while (i < MAX) {
        printf("Enter command (9 to end input): ");
        if (scanf("%d", &command)!= 1) { // 错误处理：检查输入有效性
            printf("Invalid input. Please enter a number.\n");
            while (getchar()!= '\n'); // 清除无效输入
            continue; // 继续请求输入
        }
        if (command == 9) {
            break;
        }
        commands[i][0] = command;
        if (command == 5) { // 只有在命令是前进时才请求距离
            printf("Enter distance: ");
            if (scanf("%d", &commands[i][1])!= 1) { // 错误处理：检查输入有效性
                printf("Invalid input. Please enter a number.\n");
                while (getchar()!= '\n'); // 清除无效输入
                continue; // 继续请求输入
            }
        }
        i++;
    }
}

// 向右转模块
int turnRight(int d) {
    return (d + 1) % 4;
}

// 向左转模块
int turnLeft(int d) {
    return (d + 3) % 4;
}

// 移动笔模块
void movePen(bool down, int a[][50], int *x, int *y, int dir, int dist) {
    // 确定方向的坐标变化
    int dx = (dir == 1) - (dir == 0); // 向右 (-1) 或 向左 (+1)
    int dy = (dir == 3) - (dir == 2); // 向下 (-1) 或 向上 (+1)

    for (int i = 0; i < dist; i++) {
        // 更新坐标
        *x += dx;
        *y += dy;

        // 检查边界并处理
        *x = (*x < 0) ? 0 : (*x >= 50 ? 49 : *x);
        *y = (*y < 0) ? 0 : (*y >= 50 ? 49 : *y);

        // 在笔落下时绘图
        if (down) {
            a[*y][*x] = 1; // 注意坐标顺序 (y, x)
        }
    }
}

// 打印地板模块
void printArray(int a[][50]) {
    printf("The drawing is:\n");
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            printf("%c", a[i][j] ? '*' : ' ');
        }
        printf("\n");
    }
}

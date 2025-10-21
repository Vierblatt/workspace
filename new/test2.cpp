#include <stdio.h>
#include <stdbool.h>

#define MAX 100         // 最大命令数量
#define SIZE 50         // 画布大小
#define PEN_UP 1        // 命令：提笔
#define PEN_DOWN 2      // 命令：落笔
#define TURN_RIGHT 3    // 命令：右转
#define TURN_LEFT 4     // 命令：左转
#define MOVE_FORWARD 5  // 命令：前进
#define PRINT_BOARD 6   // 命令：打印画布
#define END_INPUT 9     // 命令：结束输入

// 函数声明
void getCommands(int commands[MAX][2]);
int turnRight(int d);
int turnLeft(int d);
void movePen(bool down, int board[SIZE][SIZE], int *x, int *y, int dir, int dist);
void printBoard(int board[SIZE][SIZE]);

int main(void) {
    int commandArray[MAX][2] = {0};
    int count = 0;
    int board[SIZE][SIZE] = {0};
    bool penDown = false;
    int direction = 0;  // 初始方向向右 (0: 右, 1: 下, 2: 左, 3: 上)
    int x = 0, y = 0;

    getCommands(commandArray);

    while (count < MAX && commandArray[count][0] != END_INPUT) {
        int command = commandArray[count][0];
        int distance;

        // 命令合法性检查
        if (command < PEN_UP || command > PRINT_BOARD) {
            count++;
            continue;
        }

        switch (command) {
            case PEN_UP:
                penDown = false;
                break;
            case PEN_DOWN:
                penDown = true;
                break;
            case TURN_RIGHT:
                direction = turnRight(direction);
                break;
            case TURN_LEFT:
                direction = turnLeft(direction);
                break;
            case MOVE_FORWARD:
                distance = commandArray[count][1];
                if (distance < 0) {
                    printf("Invalid distance. Skipping command.\n");
                    break;
                }
                movePen(penDown, board, &x, &y, direction, distance);
                break;
            case PRINT_BOARD:
                printBoard(board);
                break;
        }
        count++;
    }
    return 0;
}

// 获取用户输入命令
void getCommands(int commands[MAX][2]) {
    int i = 0, command;

    while (i < MAX) {
        printf("Enter command (9 to end input): ");
        if (scanf("%d", &command) != 1 || command < 1 || command > 9) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');  // 清空无效输入
            continue;
        }

        commands[i][0] = command;
        if (command == MOVE_FORWARD) {
            printf("Enter distance: ");
            if (scanf("%d", &commands[i][1]) != 1 || commands[i][1] < 0) {
                printf("Invalid distance. Please try again.\n");
                while (getchar() != '\n');
                continue;
            }
        }
        if (command == END_INPUT) {
            break;
        }
        i++;
    }
}

// 右转：顺时针方向变化
int turnRight(int d) {
    return (d + 1) % 4;
}

// 左转：逆时针方向变化
int turnLeft(int d) {
    return (d + 3) % 4;  // 等价于 (d - 1 + 4) % 4
}

// 移动画笔
void movePen(bool down, int board[SIZE][SIZE], int *x, int *y, int dir, int dist) {
    int dx = 0, dy = 0;

    // 根据方向设定移动增量
    switch (dir) {
        case 0: dx = 1; break;   // 向右
        case 1: dy = 1; break;   // 向下
        case 2: dx = -1; break;  // 向左
        case 3: dy = -1; break;  // 向上
    }

    // 逐步移动，检查边界并绘制
    for (int i = 0; i < dist; i++) {
        int newX = *x + dx;
        int newY = *y + dy;

        if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
            *x = newX;
            *y = newY;
            if (down) {
                board[*y][*x] = 1;  // 落笔状态下标记画布
            }
        } else {
            printf("Boundary reached. Stopping movement.\n");
            break;  // 防止越界
        }
    }
}

// 打印画布
void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", board[i][j] ? '*' : ' ');
        }
        printf("\n");
    }
}

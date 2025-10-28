#include "news.h"

// 用户注册函数
void registerUser() {
    User *newUser = (User *)malloc(sizeof(User));
    printf("请输入用户名: ");
    scanf("%s", newUser->username);
    // 检查用户名是否已存在
    User *current = userHead;
    while (current!= NULL) {
        if (strcmp(current->username, newUser->username) == 0) {
            printf("用户名已存在，请重新选择。\n");
            free(newUser);
            return;
        }
        current = current->next;
    }
    printf("请输入密码: ");
    scanf("%s", newUser->password);
    printf("请选择用户类型(普通用户/管理员): ");
    scanf("%s", newUser->type);

    newUser->next = userHead;
    userHead = newUser;

    saveUsersToFile();

    printf("注册成功！\n");
}

// 用户登录函数
User *login() {
    char username[50];
    char password[50];
    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入密码: ");
    scanf("%s", password);

    User *current = userHead;
    while (current!= NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            printf("登录成功，欢迎 %s！\n", current->username);
            return current;
        }
        current = current->next;
    }

    printf("用户名或密码错误，请重新登录。\n");
    return NULL;
}

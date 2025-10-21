#ifndef NEWS_H
#define NEWS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// 新闻结构体
typedef struct News {
    char title[100];
    char content[1000];
    char publisher[50];
    char category[20];
    char date[20];
    struct News *next;
} News;

// 用户结构体
typedef struct User {
    char username[50];
    char password[50];
    char type[20];
    struct User *next;
} User;

// 全局变量声明
extern News *newsHead;
extern User *userHead;

// 函数声明
void loadNewsFromFile();
void loadUsersFromFile();
void saveNewsToFile();
void saveUsersToFile();
void registerUser();
User *login();
void displayNews(const News *node);
void browseNews();
void searchNews();
void addComment(News *news);
void manageNews(User *user);
void manageUsers(User *user);
void sortNews();
void userStatistics(User *user);
void adminStatistics();

#endif // NEWS_H


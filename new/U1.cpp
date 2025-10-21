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

// 全局变量，存储新闻链表头指针和用户链表头指针
News *newsHead = NULL;
User *userHead = NULL;

// 从文件加载新闻数据到链表
void loadNewsFromFile() {
    FILE *fp = fopen("news.txt", "r");
    if (fp == NULL) {
        printf("无法打开新闻文件。\n");
        return;
    }

    News *current = NULL;
    while (!feof(fp)) {
        News *newNews = (News *)malloc(sizeof(News));
        if (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", newNews->title, newNews->content, newNews->publisher, newNews->category, newNews->date)!= 5) {
            // 处理文件格式错误
            printf("新闻文件格式错误，请检查文件内容。\n");
            free(newNews);
            continue;
        }
        newNews->next = NULL;

        if (newsHead == NULL) {
            newsHead = newNews;
            current = newsHead;
        } else {
            current->next = newNews;
            current = current->next;
        }
    }

    fclose(fp);
}

// 从文件加载用户数据到链表
void loadUsersFromFile() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("无法打开用户文件。\n");
        return;
    }

    User *current = NULL;
    while (!feof(fp)) {
        User *newUser = (User *)malloc(sizeof(User));
        if (fscanf(fp, "%[^,],%[^,],%[^\n]\n", newUser->username, newUser->password, newUser->type)!= 3) {
            // 处理文件格式错误
            printf("用户文件格式错误，请检查文件内容。\n");
            free(newUser);
            continue;
        }
        newUser->next = NULL;

        if (userHead == NULL) {
            userHead = newUser;
            current = userHead;
        } else {
            current->next = newUser;
            current = current->next;
        }
    }

    fclose(fp);
}

// 将新闻链表数据保存到文件
void saveNewsToFile() {
    FILE *fp = fopen("news.txt", "w");
    if (fp == NULL) {
        printf("无法打开新闻文件进行保存。\n");
        return;
    }

    News *current = newsHead;
    while (current!= NULL) {
        fprintf(fp, "%s,%s,%s,%s,%s\n", current->title, current->content, current->publisher, current->category, current->date);
        current = current->next;
    }

    fclose(fp);
}

// 将用户链表数据保存到文件
void saveUsersToFile() {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) {
        printf("无法打开用户文件进行保存。\n");
        return;
    }

    User *current = userHead;
    while (current!= NULL) {
        fprintf(fp, "%s,%s,%s\n", current->username, current->password, current->type);
        current = current->next;
    }

    fclose(fp);
}

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

// 显示新闻函数
void displayNews(const News *node) {
    if (node == NULL) {
        printf("新闻节点为空，无法显示新闻内容。\n");
        return; // 增加错误处理，避免空指针访问
    }
    
    printf("标题: %s\n", node->title);
    printf("内容: %s\n", node->content);
    printf("发布者: %s\n", node->publisher);
    printf("分类: %s\n", node->category);
    printf("日期: %s\n", node->date);
}


// 浏览新闻函数
void browseNews() {
    News *current = newsHead;
    while (current!= NULL) {
        displayNews(current);
        printf("-----------------\n");
        current = current->next;
    }
}


// 搜索新闻函数
void searchNews() {
    int choice;
    printf("请选择搜索方式:\n");
    printf("1. 按标题关键字搜索\n");
    printf("2. 按分类搜索\n");
    printf("3. 按发布时间搜索\n");
    printf("请选择: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            char keyword[50];
            printf("请输入标题关键字: ");
            scanf("%s", keyword);
            News *current = newsHead;
            while (current!= NULL) {
                if (strstr(current->title, keyword)!= NULL) {
                    displayNews(current);
                    printf("-----------------\n");
                }
                current = current->next;
            }
            break;
        }
        case 2: {
            char category[20];
            printf("请输入新闻分类: ");
            scanf("%s", category);
            News *current = newsHead;
            while (current!= NULL) {
                if (strcmp(current->category, category) == 0) {
                    displayNews(current);
                    printf("-----------------\n");
                }
                current = current->next;
            }
            break;
        }
        case 3: {
            char startDate[20];
            char endDate[20];
            printf("请输入开始日期(格式: yyyy-mm-dd): ");
            scanf("%s", startDate);
            if (strlen(startDate)!= 10 || startDate[4]!= '-' || startDate[7]!= '-') {
                printf("开始日期格式不正确，请重新输入。\n");
                return;
            }
            printf("请输入结束日期(格式: yyyy-mm-dd): ");
            scanf("%s", endDate);
            if (strlen(endDate)!= 10 || endDate[4]!= '-' || endDate[7]!= '-') {
                printf("结束日期格式不正确，请重新输入。\n");
                return;
            }
            News *current = newsHead;
            while (current!= NULL) {
                if (strcmp(current->date, startDate) >= 0 && strcmp(current->date, endDate) <= 0) {
                    displayNews(current);
                    printf("-----------------\n");
                }
                current = current->next;
            }
            break;
        }
        default:
            printf("无效选择，请重新输入。\n");
    }
}

// 添加评论函数
void addComment(News *news) {
    char comment[500];
    printf("请输入评论内容: ");
    scanf(" %[^\n]", comment);
    strcat(news->content, "\n评论: ");
    strcat(news->content, comment);
    saveNewsToFile();
    printf("评论成功！\n");
}

// 管理新闻函数（管理员）
void manageNews(User *user) {

    int choice;
    do {
        printf("\n---新闻管理菜单---\n");
        printf("1. 添加新闻\n");
        printf("2. 修改新闻\n");
        printf("3. 删除新闻\n");
        printf("4. 退出新闻管理菜单\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                News *newNews = (News *)malloc(sizeof(News));
                printf("请输入新闻标题: ");
                scanf("%s", newNews->title);
                if (strlen(newNews->title) == 0) {
                    printf("新闻标题不能为空，请重新输入。\n");
                    free(newNews);
                    break;
                }
                printf("请输入新闻内容: ");
                scanf(" %[^\n]", newNews->content);
                if (strlen(newNews->content) == 0) {
                    printf("新闻内容不能为空，请重新输入。\n");
                    free(newNews);
                    break;
                }
                printf("请输入发布者: ");
                scanf("%s", newNews->publisher);
                if (strlen(newNews->publisher) == 0) {
                    printf("发布者不能为空，请重新输入。\n");
                    free(newNews);
                    break;
                }

                // 提供分类选择
                printf("请选择新闻分类(1: 通知, 2: 公告, 3: 简讯): ");
                int categoryChoice;
                scanf("%d", &categoryChoice);

                switch (categoryChoice) {
                    case 1:
                        strcpy(newNews->category, "通知");
                        break;
                    case 2:
                        strcpy(newNews->category, "公告");
                        break;
                    case 3:
                        strcpy(newNews->category, "简讯");
                        break;
                    default:
                        printf("无效的选择，请重新输入。\n");
                        free(newNews);
                        break;
                }

                // 检查日期输入
                printf("请输入发布日期(格式: yyyy-mm-dd): ");
                scanf("%s", newNews->date);
                if (strlen(newNews->date)!= 10 || newNews->date[4]!= '-' || newNews->date[7]!= '-') {
                    printf("日期格式不正确，请重新输入。\n");
                    free(newNews);
                    break;
                }


                newNews->next = newsHead;
                newsHead = newNews;

                saveNewsToFile();

                printf("新闻添加成功！\n");
                break;
            }
           case 2: {
    char title[100];
    printf("请输入要修改的新闻标题: ");
    scanf("%s", title);
    News *current = newsHead;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            printf("请输入新的新闻标题: ");
            scanf("%s", current->title);
            if (strlen(current->title) == 0) {
                printf("新闻标题不能为空，请重新输入。\n");
                break;
            }
            printf("请输入新的新闻内容: ");
            scanf(" %[^\n]", current->content);
            if (strlen(current->content) == 0) {
                printf("新闻内容不能为空，请重新输入。\n");
                break;
            }
            printf("请输入新的发布者: ");
            scanf("%s", current->publisher);
            if (strlen(current->publisher) == 0) {
                printf("发布者不能为空，请重新输入。\n");
                break;
            }
            printf("请选择新的新闻分类:\n1. 通知\n2. 公告\n3. 简讯\n");
            int categoryChoice;
            scanf("%d", &categoryChoice);
            switch (categoryChoice) {
                case 1:
                    strcpy(current->category, "通知");
                    break;
                case 2:
                    strcpy(current->category, "公告");
                    break;
                case 3:
                    strcpy(current->category, "简讯");
                    break;
                default:
                    printf("无效的新闻分类，请重新输入。\n");
                    break;
            }
            printf("请输入新的发布日期(格式: yyyy-mm-dd): ");
            scanf("%s", current->date);
            if (strlen(current->date) != 10 || current->date[4] != '-' || current->date[7] != '-') {
                printf("日期格式不正确，请重新输入。\n");
                break;
            }

            saveNewsToFile();

            printf("新闻修改成功！\n");
            break;
        }
        current = current->next;
    }
    if (current == NULL) {
        printf("未找到指定新闻。\n");
    }
    break;
}

            case 3: {
                char title[100];
                printf("请输入要删除的新闻标题: ");
                scanf("%s", title);
                News *prev = NULL;
                News *current = newsHead;
                while (current!= NULL) {
                    if (strcmp(current->title, title) == 0) {
                        if (prev == NULL) {
                            newsHead = current->next;
                        } else {
                            prev->next = current->next;
                        }
                        free(current);

                        saveNewsToFile();

                        printf("新闻删除成功！\n");
                        break;
                    }
                    prev = current;
                    current = current->next;
                }
                if (current == NULL) {
                    printf("未找到指定新闻。\n");
                }
                break;
            }
            case 4:
                break;
            default:
                printf("无效选择，请重新输入。\n");
        }
    } while (choice!= 4);
}

// 管理用户函数（管理员）
void manageUsers(User *user) {
    int choice;
    do {
        // 显示用户管理菜单，提供给管理员操作选项
        printf("\n---用户管理菜单---\n");
        printf("1. 添加用户\n");
        printf("2. 删除用户\n");
        printf("3. 修改用户信息\n");
        printf("4. 退出用户管理菜单\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // 调用注册用户函数，复用之前定义的注册功能
                registerUser();
                break;
            case 2: {
                char username[50];
                // 提示管理员输入要删除的用户名
                printf("请输入要删除的用户名: ");
                scanf("%s", username);

                User *prev = NULL;
                User *current = userHead;
                // 遍历用户链表，查找要删除的用户
                while (current!= NULL) {
                    if (strcmp(current->username, username) == 0) {
                        // 如果要删除的用户是链表头节点
                        if (prev == NULL) {
                            userHead = current->next;
                        } else {
                            // 如果不是头节点，调整前一个节点的next指针
                            prev->next = current->next;
                        }
                        free(current);  // 释放要删除用户的内存空间

                        saveUsersToFile();  // 将更新后的用户链表保存到文件

                        printf("用户删除成功！\n");
                        break;
                    }
                    prev = current;
                    current = current->next;
                }
                // 如果遍历完链表未找到指定用户，给出提示
                if (current == NULL) {
                    printf("未找到指定用户。\n");
                }
                break;
            }
            case 3: {
                char username[50];
                // 提示管理员输入要修改信息的用户名
                printf("请输入要修改信息的用户名: ");
                scanf("%s", username);

                User *current = userHead;
                // 遍历用户链表，查找要修改信息的用户
                while (current!= NULL) {
                    if (strcmp(current->username, username) == 0) {
                        char newUsername[50];
                        // 提示管理员输入新的用户名
                        printf("请输入新的用户名: ");
                        scanf("%s", newUsername);
                        // 检查新用户名是否为空，为空则提示重新输入
                        if (strlen(newUsername) == 0) {
                            printf("用户名不能为空，请重新输入。\n");
                            break;
                        }

                        char newPassword[50];
                        // 提示管理员输入新的密码
                        printf("请输入新的密码: ");
                        scanf("%s", newPassword);
                        // 检查新密码是否为空，为空则提示重新输入
                        if (strlen(newPassword) == 0) {
                            printf("密码不能为空，请重新输入。\n");
                            break;
                        }

                        char newType[20];
                        // 提示管理员输入新的用户类型（普通用户/管理员）
                        printf("请选择新的用户类型(普通用户/管理员): ");
                        scanf("%s", newType);
                        // 检查新用户类型是否合法，不合法则提示重新输入
                        if (strcmp(newType, "普通用户")!= 0 && strcmp(newType, "管理员")!= 0) {
                            printf("无效的用户类型，请重新输入。\n");
                            break;
                        }

                        // 更新用户信息
                        strcpy(current->username, newUsername);
                        strcpy(current->password, newPassword);
                        strcpy(current->type, newType);

                        saveUsersToFile();  // 将更新后的用户链表保存到文件

                        printf("用户信息修改成功！\n");
                        break;
                    }
                    current = current->next;
                }
                // 如果遍历完链表未找到指定用户，给出提示
                if (current == NULL) {
                    printf("未找到指定用户。\n");
                }
                break;
            }
            case 4:
                break;
            default:
                // 处理管理员输入的无效选择
                printf("无效选择，请重新输入。\n");
        }
    } while (choice!= 4);
}

// 比较函数，用于按发布日期升序排序
int compareByDate(const void *a, const void *b) {
    return strcmp(((News *)a)->date, ((News *)b)->date);
}

// 比较函数，用于按发布日期降序排序
int compareByDateDesc(const void *a, const void *b) {
    return strcmp(((News *)b)->date, ((News *)a)->date);
}

// 排序新闻函数
void sortNews() {
    int choice;
    printf("请选择排序方式:\n");
    printf("1. 按发布日期升序排序\n");
    printf("2. 按发布日期降序排序\n");
    printf("请选择: ");
    scanf("%d", &choice);

    News *newsArray[100];  // 假设最多100条新闻，可根据实际情况调整大小
    int count = 0;
    News *current = newsHead;
    while (current!= NULL) {
        newsArray[count++] = current;
        current = current->next;
    }

    switch (choice) {
        case 1:
            qsort(newsArray, count, sizeof(News *), compareByDate);
            break;
        case 2:
            qsort(newsArray, count, sizeof(News *), compareByDateDesc);
            break;
        default:
            printf("无效选择，请重新输入。\n");
            return;
    }

    newsHead = NULL;
    for (int i = 0; i < count; i++) {
        newsArray[i]->next = newsHead;
        newsHead = newsArray[i];
    }

    printf("新闻排序成功！\n");
}

// 用户统计新闻发布情况函数（普通用户）
void userStatistics(User *user) {
    char startDate[20];
    char endDate[20];
    printf("请输入开始日期(格式: yyyy-mm-dd): ");
    scanf("%s", startDate);
    if (strlen(startDate)!= 10 || startDate[4]!= '-' || startDate[7]!= '-') {
        printf("开始日期格式不正确，请重新输入。\n");
        return;
    }
    printf("请输入结束日期(格式: yyyy-mm-dd): ");
    scanf("%s", endDate);
    if (strlen(endDate)!= 10 || endDate[4]!= '-' || endDate[7]!= '-') {
        printf("结束日期格式不正确，请重新输入。\n");
        return;
    }

    int count = 0;
    News *current = newsHead;
    while (current!= NULL) {
        if (strcmp(current->publisher, user->username) == 0 && strcmp(current->date, startDate) >= 0 && strcmp(current->date, endDate) <= 0) {
            count++;
        }
        current = current->next;
    }

    printf("在 %s 到 %s 期间，你发布了 %d 条新闻。\n", startDate, endDate, count);
}

// 管理员统计新闻发布情况函数
void adminStatistics() {
    char startDate[20];
    char endDate[20];
    printf("请输入开始日期(格式: yyyy-mm-dd): ");
    scanf("%s", startDate);
    if (strlen(startDate)!= 10 || startDate[4]!= '-' || startDate[7]!= '-') {
        printf("开始日期格式不正确，请重新输入。\n");
        return;
    }
    printf("请输入结束日期(格式: yyyy-mm-dd): ");
    scanf("%s", endDate);
    if (strlen(endDate)!= 10 || endDate[4]!= '-' || endDate[7]!= '-') {
        printf("结束日期格式不正确，请重新输入。\n");
        return;
    }

    User *currentUser = userHead;
    while (currentUser!= NULL) {
        int count = 0;
        News *currentNews = newsHead;
        while (currentNews!= NULL) {
            if (strcmp(currentNews->publisher, currentUser->username) == 0 && strcmp(currentNews->date, startDate) >= 0 && strcmp(currentNews->date, endDate) <= 0) {
                count++;
            }
            currentNews = currentNews->next;
        }
        if (count > 0) {
            printf("%s 在 %s 到 %s 期间发布了 %d 条新闻。\n", currentUser->username, startDate, endDate, count);
        }
        currentUser = currentUser->next;
    }
}

int main() {
    setlocale(LC_ALL, "zh_CN.UTF-8");
    int choice;
    User *loggedInUser = NULL;

    loadNewsFromFile();
    loadUsersFromFile();

    do {
    printf("\n---校园新闻发布管理系统---\n");
    printf("1. 注册用户\n");
    printf("2. 登录\n");
    printf("3. 浏览新闻\n");
    printf("4. 搜索新闻\n");
    printf("5. 退出\n");
    printf("请选择操作: ");
    if (scanf("%d", &choice) != 1) {
        printf("输入无效，请输入一个数字。\n");
        // 清理输入缓冲区
        while (getchar() != '\n');
        continue; // 重新循环，等待输入
    }

    switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loggedInUser = login();
            if (loggedInUser != NULL) {
                int adminChoice;
                if (strcmp(loggedInUser->type, "管理员") == 0) {
                    do {
                        printf("\n---管理员菜单---\n");
                        printf("1. 管理新闻\n");
                        printf("2. 管理用户\n");
                        printf("3. 排序新闻\n");
                        printf("4. 统计新闻发布情况\n");
                        printf("5. 退出管理员菜单\n");
                        printf("请选择操作: ");
                        if (scanf("%d", &adminChoice) != 1) {
                            printf("输入无效，请输入一个数字。\n");
                            // 清理输入缓冲区
                            while (getchar() != '\n');
                            continue; // 重新循环，等待输入
                        }

                        switch (adminChoice) {
                            case 1: manageNews(loggedInUser); break;
                            case 2: manageUsers(loggedInUser); break;
                            case 3: sortNews(); break;
                            case 4: adminStatistics(); break;
                            case 5: break;
                            default: printf("无效选择，请重新输入。\n"); break;
                        }
                    } while (adminChoice != 5);
                } else {
                    int userChoice;
                    do {
                        printf("\n---普通用户菜单---\n");
                        printf("1. 浏览新闻\n");
                        printf("2. 搜索新闻\n");
                        printf("3. 发表评论\n");
                        printf("4. 统计个人新闻发布情况\n");
                        printf("5. 退出普通用户菜单\n");
                        printf("请选择操作: ");
                        if (scanf("%d", &userChoice) != 1) {
                            printf("输入无效，请输入一个数字。\n");
                            // 清理输入缓冲区
                            while (getchar() != '\n');
                            continue; // 重新循环，等待输入
                        }

                        switch (userChoice) {
                            case 1: browseNews(); break;
                            case 2: searchNews(); break;
                            case 3: {
                                char title[100];
                                printf("请输入要评论的新闻标题: ");
                                scanf("%s", title);
                                News *newsToComment = NULL;
                                for (News *current = newsHead; current != NULL; current = current->next) {
                                    if (strcmp(current->title, title) == 0) {
                                        newsToComment = current;
                                        break;
                                    }
                                }
                                if (newsToComment != NULL) {
                                    addComment(newsToComment);
                                } else {
                                    printf("未找到指定新闻。\n");
                                }
                                break;
                            }
                            case 4: userStatistics(loggedInUser); break;
                            case 5: break;
                            default: printf("无效选择，请重新输入。\n"); break;
                        }
                    } while (userChoice != 5);
                }
            }
            break;
        case 3: browseNews(); break;
        case 4: searchNews(); break;
        case 5: 
            saveNewsToFile();
            saveUsersToFile();
            printf("感谢使用，再见！\n");
            break;
        default: 
            printf("无效选择，请重新输入。\n");
    }
} while (choice != 5);


    return 0;
}


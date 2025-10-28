#include "news.h"

// 全局变量定义
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

// 显示新闻函数
void displayNews(const News *node) {
    if (node == NULL) {
        printf("新闻节点为空，无法显示新闻内容。\n");
        return;
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

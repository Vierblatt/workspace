#include "news.h"

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
            while (getchar() != '\n');
            continue;
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
                                while (getchar() != '\n');
                                continue;
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
                                while (getchar() != '\n');
                                continue;
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

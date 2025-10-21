#include "news.h"
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
                if (strlen(newNews->date) != 10 || newNews->date[4] != '-' || newNews->date[7] != '-') {
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
                while (current != NULL) {
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
    } while (choice != 4);
}

// 管理用户函数（管理员）
void manageUsers(User *user) {
    int choice;
    do {
        printf("\n---用户管理菜单---\n");
        printf("1. 添加用户\n");
        printf("2. 删除用户\n");
        printf("3. 修改用户信息\n");
        printf("4. 退出用户管理菜单\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2: {
                char username[50];
                printf("请输入要删除的用户名: ");
                scanf("%s", username);

                User *prev = NULL;
                User *current = userHead;
                while (current != NULL) {
                    if (strcmp(current->username, username) == 0) {
                        if (prev == NULL) {
                            userHead = current->next;
                        } else {
                            prev->next = current->next;
                        }
                        free(current);

                        saveUsersToFile();

                        printf("用户删除成功！\n");
                        break;
                    }
                    prev = current;
                    current = current->next;
                }
                if (current == NULL) {
                    printf("未找到指定用户。\n");
                }
                break;
            }
            case 3: {
                char username[50];
                printf("请输入要修改信息的用户名: ");
                scanf("%s", username);

                User *current = userHead;
                while (current != NULL) {
                    if (strcmp(current->username, username) == 0) {
                        char newUsername[50];
                        printf("请输入新的用户名: ");
                        scanf("%s", newUsername);
                        if (strlen(newUsername) == 0) {
                            printf("用户名不能为空，请重新输入。\n");
                            break;
                        }

                        char newPassword[50];
                        printf("请输入新的密码: ");
                        scanf("%s", newPassword);
                        if (strlen(newPassword) == 0) {
                            printf("密码不能为空，请重新输入。\n");
                            break;
                        }

                        char newType[20];
                        printf("请选择新的用户类型(普通用户/管理员): ");
                        scanf("%s", newType);
                        if (strcmp(newType, "普通用户") != 0 && strcmp(newType, "管理员") != 0) {
                            printf("无效的用户类型，请重新输入。\n");
                            break;
                        }

                        strcpy(current->username, newUsername);
                        strcpy(current->password, newPassword);
                        strcpy(current->type, newType);

                        saveUsersToFile();

                        printf("用户信息修改成功！\n");
                        break;
                    }
                    current = current->next;
                }
                if (current == NULL) {
                    printf("未找到指定用户。\n");
                }
                break;
            }
            case 4:
                break;
            default:
                printf("无效选择，请重新输入。\n");
        }
    } while (choice != 4);
}

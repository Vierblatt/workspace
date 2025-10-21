#include <stdio.h>
#include <string.h>
int main() {
    int upper = 0, lower = 0, digit = 0, space = 0, other = 0;
    char*p,s[20];
    printf("请输入一行文字：");
    fgets(s, sizeof(s), stdin); 
    for (char *p = s; *p != '\0'&& *p != '\n'; p++) {
        if (*p >= 'A' && *p <= 'Z') {
            upper++;
        } else if (*p >= 'a' && *p <= 'z') {
            lower++;
        } else if (*p >= '0' && *p <= '9') {
            digit++;
        } else if (*p == ' ') {
            space++;
        } else {
            other++;
        }
    }
    printf("大写字母数量: %d\n", upper);
    printf("小写字母数量: %d\n", lower);
    printf("数字数量: %d\n", digit);
    printf("空格数量: %d\n", space);
    printf("其他字符数量: %d\n", other);
    return 0; 
}

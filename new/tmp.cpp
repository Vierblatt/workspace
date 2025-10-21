#include <stdio.h>
int n=3,sum=0;
int main() {
    for (int i = 0; i < n; i++) {
        sum+=i*10+1;
    }
    printf("%d", sum);
    return 0;
}
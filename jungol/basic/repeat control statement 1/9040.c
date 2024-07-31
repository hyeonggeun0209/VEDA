#include <stdio.h>

int main() {
    int num = 1;
    int n;
    int sum = 0;

    scanf("%d", &n);

    while(num <= n) {
       sum += num++;
    }

    printf("%d\n", sum);

    return 0;
}
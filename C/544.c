#include <stdio.h>

int main() {
    int n,i;
    int sum = 0;
    scanf("%d", &n);

    for (i = n; i <= 100; i++) {
        sum += i;
    }

    printf("%d", sum);

    return 0;
}
#include <stdio.h>

void add(int n) {
    int i, sum = 0;
    for (i = 1; i <= n; i++) {
        sum += i;
        if (sum > n) {
            printf("%d %d", i, sum);
            break;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    add(n);

    return 0;
}
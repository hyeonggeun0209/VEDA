#include <stdio.h>

void add(int n) {
    int i, cnt = 0, sum = 0;
    for (i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            sum += i;
            cnt++;
        }
        if (sum >= n) {
            printf("%d %d", cnt, sum);
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
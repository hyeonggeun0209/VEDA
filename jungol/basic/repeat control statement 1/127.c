#include <stdio.h>

int main() {
    int n;
    int sum = 0;
    int cnt = 0;

    scanf("%d ", &n);

    while(0 <= n && n <= 100) {
        sum += n;
        cnt++;
        scanf("%d ", &n);
    }

    printf("sum : %d\n", sum);
    printf("avg : %.1f\n", (double) sum/cnt);

    return 0;
}
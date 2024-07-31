#include <stdio.h>

int main() {
    int n;
    int sum = 0;
    int cnt = 0;

    scanf("%d ", &n);

    do {
        sum += n;
        cnt++;
        scanf("%d ", &n);
    } while(n < 100);

    sum += n;
    cnt++;

    printf("%d\n", sum);
    printf("%.1f\n", (double) sum/cnt);

    return 0;
}
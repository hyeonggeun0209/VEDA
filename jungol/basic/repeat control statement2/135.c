#include <stdio.h>

int main() {

    int n,m, i, t;
    int sum = 0, cnt = 0;

    scanf("%d %d", &n, &m);

    if (n > m) {
        t = n;
        n = m;
        m = t;
    }

    for (i = n; i <= m; i++) {
        if(i % 3 == 0 || i % 5 == 0) {
            sum += i;
            cnt++;
        }
    }

    printf("sum : %d\n", sum);
    printf("avg : %.1f", (double) sum/cnt);

    return 0;
}
#include <stdio.h>

int main() {

    int n, m, i, sum = 0;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d ", &m);
        sum += m;
    }

    printf("%.2f", (double)sum/n);
    return 0;
}
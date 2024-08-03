#include <stdio.h>

int main() {

    int n,m;
    int i, t;
    scanf("%d %d", &n, &m);

    if (n < m) {
        t = n;
        n = m;
        m = t;
    }

    for (i = m; i <= n; i++) {
        printf("%d ", i);
    }

    return 0;
}
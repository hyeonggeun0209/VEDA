#include<stdio.h>

int main() {
    int n, m;
    int i, j;
    int num = 1;
    scanf("%d %d", &n, &m);

    for (i = 0;i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", num++);
        }
        printf("\n");
    }
    return 0;
}
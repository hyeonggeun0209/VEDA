#include <stdio.h>

void print(int n) {
    int i, j, cnt=1;
    for (i = 0; i <= n; i++) {
        for (j = 0; j < i; j++) {
            printf("%d ", cnt++);
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    print(n);

    return 0;
}
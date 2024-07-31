#include <stdio.h>

void print(int n) {
    int i, j ;
    char c = 'A';
    for (i = 0; i <= n; i++) {
        for (j = n; j > i; j--) {
            printf("%c", c++);
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
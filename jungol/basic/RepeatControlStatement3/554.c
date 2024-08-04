#include <stdio.h>

void print(int n) {
    int i, j;
    int num = 1;
    char c = 'A';
    for(i = 1; i <= n; i++) {
        for(j = i; j <= n; j++) {
            printf("%d ", num++);
        }
        for(j = 0; j < i; j++) {
            printf("%c ", c++);
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
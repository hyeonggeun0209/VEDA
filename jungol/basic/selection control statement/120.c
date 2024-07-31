#include <stdio.h>

int main() {
    int a, b;

    scanf("%d %d", &a, &b);

    int n = (a > b) ? (a - b) : (b - a);
    printf("%d", n);



    return 0;
}
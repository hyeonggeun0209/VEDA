#include <stdio.h>

int main() {

    int n, m;
    int a, b, c;

    scanf("%d", &n);
    scanf("%d", &m);

    a = n * (m % 10);
    b = n * (m % 100 / 10);
    c = n * (m / 100);

    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);
    printf("%d\n", n*m);


    return 0;
}
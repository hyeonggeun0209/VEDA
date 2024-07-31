#include <stdio.h>

int main() {

    double a,b;

    scanf("%lf %lf", &a, &b);

    int c = a * b;
    int d = (int )a * (int )b;
    printf("%d %d",c,d);

    return 0;
}
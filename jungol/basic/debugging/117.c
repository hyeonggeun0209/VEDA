#include <stdio.h>

int main() {

    double a, b, c;

    scanf("%lf %lf %lf", &a,&b, &c);

    int sum = (int)a + (int)b + (int)c;
    double d = (a + b + c) / 3;

    printf("sum %d\n",sum);
    printf("avg %d",(int)d);

    return 0;
}
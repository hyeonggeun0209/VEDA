#include<stdio.h>

int main() {

    int a = 5;
    double pi = 3.14;

    printf("원주 = %d * %d * %f = %f\n", a,2,pi,a*2*pi);

    printf("넓이 = %d * %d * %f = %f\n", a,a,pi,a*a*pi);

    return 0;
}
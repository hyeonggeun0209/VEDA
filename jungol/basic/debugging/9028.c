#include <stdio.h>

int main() {

    int a ;

    scanf("%d", &a);

    int c = a / 4;
    double d = a / 4.0;

    printf("%d / 4 = %d\n",a,c);
    printf("%d / 4.0 = %.2f",a,d);

    return 0;
}
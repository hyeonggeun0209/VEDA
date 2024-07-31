#include <stdio.h>

int main() {

    int a,b;

    scanf("%d %d", &a,&b);

    int c = a / b;
    double d = (double)a / b;

    printf("%d ",c);
    printf("%.2f",d);

    return 0;
}
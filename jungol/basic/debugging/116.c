#include <stdio.h>

int main() {

    int a,b,c ;

    scanf("%d %d %d", &a,&b,&c);

    double avg = (double)(a+b+c)/3;

    printf("%.1f",avg);

    return 0;
}
#include<stdio.h>


int main() {

    // char x, y;
    // x = -128;
    // y = -x;

    // if (x == y) printf("1\n");
    // if ((x - y) == 0) printf("2\n");
    // if ((x + y) == 2 * x) printf("3\n");
    // if (x != -y) printf("4\n");

    int a = 0, b = 0, sum1, sum2;

    sum1 = a++ +a++ +a++;
    sum2 = ++b+ ++b+ ++b;

    printf("%d %d %d %d", a, b, sum1, sum2);

    return 0;
    
}

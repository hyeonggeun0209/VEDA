#include <stdio.h>

int main() {
    int n;

    scanf("%d", &n);

    if (n == 0) printf("zero");
    else if (n > 0) printf("plus");
    else printf("minus");

    return 0;
}
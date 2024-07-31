#include <stdio.h>

int main() {
    int n;
    printf("number? ");
    scanf("%d", &n);

    while(n != 0) {
        if(0 < n) printf("positive integer\n");
        else printf("negative number\n");
        printf("number? ");
        scanf("%d", &n);
    }

    return 0;
}
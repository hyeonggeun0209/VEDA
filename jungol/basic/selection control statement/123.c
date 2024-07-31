#include <stdio.h>

int main() {
    int n;

    printf("Number? ");
    scanf("%d", &n);

    switch(n) {
        case 1 : printf("dog"); break;
        case 2 : printf("cat"); break;
        case 3 : printf("chick"); break;
        default : printf("I don't know."); break;
    }

    return 0;
}
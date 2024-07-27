#include <stdio.h>

int main() {
    int n;

    do {
        printf("1. Korea\n2. USA\n3. Japan\n4. China\nnumber? ");
        scanf("%d", &n);
        switch (n) {
        case 1: 
            printf("\nSeoul\n");
            break;
        case 2:
            printf("\nWashington\n");
            break;
        case 3:
            printf("\nTokyo\n");
            break;
        case 4:
            printf("\nBeijing\n");
            break;
        default:
            printf("\nnone\n");
            break;
        }
        printf("\n");
    } while (1 <= n && n <= 4);

    return 0;
}
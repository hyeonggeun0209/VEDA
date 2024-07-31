#include <stdio.h>

int main() {
    int i, j;

    for (i = 1; i <= 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%d ", i);
        }
        printf("\n");
    }
    
    printf("\n");

    for (i = 0; i < 5; i++) {
        for (j = 1; j <= 5; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }


    return 0;
}
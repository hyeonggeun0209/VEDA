#include <stdio.h>

int main() {

    int base, height;
    char c = 'y';

    while (c == 'Y' || c == 'y') {
        printf("Base = ");
        scanf("%d", &base);

        printf("Height = ");
        scanf("%d", &height);

        printf("Triangle width = %.1f\n", (double) base * height / 2);
        
        printf("Continue? ");
        scanf("%*c%c", &c);
    }

    return 0;
}
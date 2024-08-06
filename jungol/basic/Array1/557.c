#include <stdio.h>

int main() {
    char arr[10];
    for (int i = 0; i < 10; i++) {
        scanf(" %c", &arr[i]);
    }
    printf("%c ", arr[0]);
    printf("%c ", arr[3]);
    printf("%c ", arr[6]);
    return 0;
}
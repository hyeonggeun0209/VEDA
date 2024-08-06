#include <stdio.h>

int main() {
    char arr[26];
    for (int i = 0; i < 26; i++) {
        scanf(" %c", &arr[i]);
    }
    for (int i = 25; i >=0; i++) {
        printf("%c ", arr[i]);
    }
    return 0;
}
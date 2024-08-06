#include <stdio.h>

int main() {
    char arr[26];
    char c = 'A';
    for (int i = 0; i < 26; i++) {
        arr[i] = c++;
    }
    for (int i = 25; i >=0; i--) {
        printf("%c ", arr[i]);
    }
    return 0;
}
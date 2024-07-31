#include <stdio.h>

int main() {

    char c = 'A';
    int i;

    for (i = 0; i < 26; i++) {
        printf("%c", c++);
    }

    return 0;
}
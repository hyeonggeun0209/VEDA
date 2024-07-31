#include <stdio.h>

int main() {
    char c = 'A';

    while(c != '[') {
        printf("%c", c++);
    }

    return 0;
}
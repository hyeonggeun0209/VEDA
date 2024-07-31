#include <stdio.h>

int main() {

    int a;

    scanf("%d", &a);
    if(a <= 50.80) printf("Flyweight");
    else if(a <= 61.23) printf("Lightweight");
    else if(a <= 72.57) printf("Middleweight");
    else if(a <= 88.45) printf("Cruiserweight");
    else if(a >  88.45) printf("Heavyweight");

    return 0;
}

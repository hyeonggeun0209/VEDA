#include <iostream>
using namespace std;

int main() {

    char x, y;
    x = -128;
    y = -x;

    if (x == y) printf("1\n");
    if ((x - y) == 0) printf("2\n");
    if ((x + y) == 2 * x) printf("3\n");
    if (x != -y) printf("4\n");

    return 0;
}
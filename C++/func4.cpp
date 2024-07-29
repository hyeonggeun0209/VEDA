#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int add(int a, int &b) {
    b = a + b;
    return b;
}

int main() {
    int s = 10, t = 20;
    cout << add(s, t);

    return 0;
}
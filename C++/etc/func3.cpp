#include <iostream>
using namespace std;

long square(long a) {
    return a*a;
}

float square(float a) {
    return a * a;
}

double square(double a) {
    return a * a;
}

int main() {
    cout << square(3.0);
    cout << square(3L);

    return 0;
}
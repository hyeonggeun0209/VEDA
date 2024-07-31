#include <iostream>
using namespace std;

int main() {
    double pi = 3.14;

    auto calc = [pi](int r) -> double { return pi * r * r;};

    cout << "면적은 " << calc(3) << endl;

    int sum = 0;

    [&sum](int x, int y) { sum = x + y;} (2, 3);

    cout << "합은 " << sum << endl;
    return 0;
}
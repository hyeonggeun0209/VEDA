#include <iostream>
using namespace std;

int gcd(int a, int b) {
    int ans;
    for (int i = 1; i <= a; i++) {
        if(a % i == 0 && b % i == 0)
            ans = i;
    }
    return ans;
}

int main() {
    int a, b, c;

    cin >> a >> b;
    c = gcd(a, b);
    cout << c << endl << a*b/c;

    return 0;
}
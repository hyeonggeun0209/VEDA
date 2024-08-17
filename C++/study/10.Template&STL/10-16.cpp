#include <iostream>
#include <string>
using namespace std;

int main() {
    [](int x, int y) { cout << "합은 " << x + y << endl;} (2, 3);

    auto love = [](string a, string b) {
        cout << a << "보다 " << b <<"가 좋아" << endl;
    };

    love("돈", "너");
    love("냉면", "만두");

    // auto rove = [](auto a, auto b) {
    //     int x = 10;
    //     cout << a + b + x;
    // };
    // rove(1, 10.5);

    return 0;
}
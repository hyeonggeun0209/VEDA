#include <iostream>
using namespace std;

class Point {
    int x, y;
public:
    Point(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }
    friend ostream& operator << (ostream& stream, Point a);
    friend istream& operator >> (istream& ins, Point &a);
};

ostream& operator << (ostream& stream, Point a) {
    stream << "(" << a.x << ", " << a.y << ")";
    return stream;
}

istream& operator >> (istream& ins, Point& a) {
    cout << "x 좌표 >>";
    ins >> a.x;
    cout << "y 좌표 >>";
    ins >> a.y;
    return ins;
}

int main() {
    Point p;
    cin >> p;
    cout << p;

    return 0;
}
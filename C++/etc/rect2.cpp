#include <iostream>
using namespace std;

class Rectangle {
    public:
        int width;
        int height;
        Rectangle();
        Rectangle(int w, int h);
        Rectangle(int length);
        long getArea();
        bool isSquare();
};

Rectangle::Rectangle() : Rectangle(1) { }

Rectangle::Rectangle(int w, int h) {
    width = w;
    height = h;
}

Rectangle::Rectangle(int length) {
    width = length;
    height = length;
}

long Rectangle::getArea() {
    return width * height;
}
bool Rectangle::isSquare() {
    if(width == height) return true;
    else return false;
}

int main() {
    Rectangle rect1;
    Rectangle rect2(3, 5);
    Rectangle rect3(3);

    if(rect1.isSquare()) cout << "rect1은 정사각형이다." << endl;
    if(rect2.isSquare()) cout << "rect2은 정사각형이다." << endl;
    if(rect3.isSquare()) cout << "rect3은 정사각형이다." << endl;
    

    return 0;
}
#include <iostream>
using namespace std;

class Circle {
private:
    int radius;
public:
    Circle(const Circle& c);
    Circle();
    Circle(int r);
    ~Circle();
    double getArea() {return 3.14 * radius * radius;}
    int getRadius() { return radius;}
    void setRadius(int radius) { this->radius = radius;}
};

Circle::Circle() : Circle(1) { }

Circle::Circle(int radius) {
    this->radius = radius;
    cout << "생성자 실행 radius = " << radius << endl;
}

Circle::~Circle() {
    cout << "소멸자 실행 radius = " << radius << endl;
}

Circle::Circle(const Circle& c) {
    this->radius = c.radius;
    cout << "복사 생성자 실행 radius = " << radius << endl;
}

int main() {
    Circle src(30);
    Circle dest(src);

    cout << "원본의 면적 = " << src.getArea() << endl;
    cout << "사본의 면적 = " << dest.getArea() << endl;

    return 0;
}
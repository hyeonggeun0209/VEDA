#include <iostream>
using namespace std;

class Circle {
private:
    int radius;
public:
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

int main() {
    Circle c;
    Circle &refc = c;
    refc.setRadius(10);

    cout << c.getArea() << " " << refc.getArea() << endl;

    return 0;
}
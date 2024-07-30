#include <iostream>
#include <string>
using namespace std;

class Point {
private:
    int x, y;
public:
    void set(int x, int y) { this->x = x; this->y = y;}
    void showPoint() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

class ColorPoint : public Point {
private:
    string color;
public:
    void setColor(string color) { this->color = color;}
    void showColorPoint();
};

void ColorPoint::showColorPoint() {
    cout << color << " : ";
    showPoint();
}

int main() {
    // Up-Casting 
    // ColorPoint cp;
    // ColorPoint* pDer = &cp;
    // Point* pBase = pDer;

    // pDer->set(3,4);
    // pDer->setColor("Red");
    // pDer->showColorPoint();
    // pBase->set(1,1);
    // pDer->showColorPoint();

    // Down-Casting
    ColorPoint cp;
    ColorPoint* pDer;
    Point* pBase = &cp;

    pBase->set(3,4);
    pBase->showPoint();

    pDer = (ColorPoint*) pBase;
    pDer->setColor("Red");
    pDer->showColorPoint();


    return 0;
}

#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <iostream>

class Calculator
{
private:
    double num1;
    double num2;
    char op;
public:
    Calculator(double num1 = 0, char op = ' ', double num2 = 0)
        : num1(num1), op(op), num2(num2){}
    void input() { std::cin >> num1 >> op >> num2; }
    double doCalculate();
};

#endif // CALCULATOR_H

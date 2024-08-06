#include "calculator.h"

// Calculator::Calculator() {}
double Calculator::doCalculate() {

    double result=0;
    switch(op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case 'x': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
    };
    return result;

}

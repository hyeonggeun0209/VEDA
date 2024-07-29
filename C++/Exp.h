class Exp {
private:
    int exp;
    int base;
public:
    Exp(int base = 1, int exp = 1) {
    this->base = base;
    this->exp = exp;
}
    int getValue();
    int getBase();
    int getExp();
    bool equals(Exp b);
};

int Exp::getValue() {
    int value = 1;
    for (int i = 0; i < exp; i++) {
        value *= base;
    }
    return value;
}

int Exp::getBase() {
    return base;
}

int Exp::getExp() {
    return exp;
}

bool Exp::equals(Exp b) {
    return (getValue() == b.getValue())? 1 : 0;
}
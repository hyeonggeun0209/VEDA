#include "product.h"

#include <iostream>

using namespace std;

Product::Product(int id, string name, string price)
          : p_id(id), p_name(name), p_price(price)
{
}

string Product::getName() const
{
    return p_name;
}

void Product::setName(string& name)
{
    p_name = name;
}

string Product::getPrice() const
{
    return p_price;
}

void Product::setPrice(string& price)
{
    p_price = price;
}

int Product::id() const
{
    return p_id;
}

// Define copy assignment operator.
bool Product::operator==(const Product &other) const {
    return (this->p_name == other.p_name);
}

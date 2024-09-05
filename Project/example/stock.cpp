#include "stock.h"

#include <iostream>

using namespace std;

Stock::Stock(int id, string section,  int quantity)
          : s_id(id), s_quantity(quantity), s_section(section)
{
}

void Stock::setP_id(int id) {
    p_id.push_back(id);
}

vector<int> Stock::getP_id() {
    return p_id;
}

void Stock::incrementQuantity() {
    s_quantity++;
}
int Stock::getQuantity() const
{
    return s_quantity;
}

void Stock::setQuantity(int quantity)
{
    s_quantity = quantity;
}

string Stock::getSection() const
{
    return s_section;
}

void Stock::setSection(string& section)
{
    s_section = section;
}

int Stock::id() const
{
    return s_id;
}

// Define copy assignment operator.
bool Stock::operator==(const Stock &other) const {
    return (this->s_section == other.s_section);
}

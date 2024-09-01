#include "stock.h"

#include <iostream>

using namespace std;

Stock::Stock(int id, int quantity, string section)
          : s_id(id), s_quantity(quantity), s_section(section)
{
}

// int Stock::getP_id() const {
//     return p_id;
// }

int Stock::getQuantity() const
{
    return s_quantity;
}

void Stock::setQuantity(string& name)
{
    s_quantity = atoi(name.c_str());
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

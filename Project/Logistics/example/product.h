#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <iostream>

using namespace std;

class Product {
public:
    Product(int id = 0, string = "", string = "");

    string getName() const;
    void setName(string&);
    string getPrice() const;
    void setPrice(string&);
    int id() const;
    bool operator==(const Product &other) const;

private:
    int p_id;
    string p_name;
    string p_price;
};
#endif          // __PRODUCT_H__

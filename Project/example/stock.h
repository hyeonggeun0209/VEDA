#ifndef __STOCK_H__
#define __STOCK_H__

#include <iostream>
#include <vector>

using namespace std;

class Stock {
public:
    Stock(int id = 0, int quantity = 0, string = "");

    // int getP_id() const;
    int  getQuantity() const;
    void setQuantity(string&);
    string getSection() const;
    void setSection(string&);
    int id() const;
    bool operator==(const Stock &other) const;

private:
    int s_id;
    vector<int> p_id;
    int s_quantity;
    string s_section;
};
#endif          // __STOCK_H__

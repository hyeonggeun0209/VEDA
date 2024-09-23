#ifndef __STOCK_H__
#define __STOCK_H__

#include <iostream>
#include <vector>

using namespace std;

class Stock {
public:
    Stock(int id = 0, string = "", int quantity = 0);
    
    void setP_id(int id);
    vector<int> getP_id();
    void incrementQuantity();
    int  getQuantity() const;
    void setQuantity(int);
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

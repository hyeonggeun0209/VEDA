#ifndef __BOX_H__
#define __BOX_H__

#include <iostream>

using namespace std;

class Box {
public:
    Box(int id = 0, string = "", string = "", string = "",bool = true);

    string getName() const;
    void setName(string&);
    string getPhoneNumber() const;
    void setPhoneNumber(string&);
    string getAddress() const;
    void setAddress(string&);
    int id() const;
    bool getState() const;
    void setState(bool&);
    bool operator==(const Box &other) const;

private:
    int m_id;
    string m_name;
    string m_phoneNumber;
    string m_address;
    bool m_state;
};
#endif          // __BOX_H__

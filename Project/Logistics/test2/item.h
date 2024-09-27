// item.h

#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    int itemID;                  // 물품 ID
    std::string customerName;    // 주문자 이름
    std::string customerAddress; // 주문자 주소
    std::string customerPhone;   // 주문자 전화번호

public:
    // Constructor
    Item(int id, const std::string& name, const std::string& address, const std::string& phone) 
        : itemID(id), customerName(name), customerAddress(address), customerPhone(phone) {}

    // Getters
    int getItemID() const { return itemID; }
    std::string getCustomerName() const { return customerName; }
    std::string getCustomerAddress() const { return customerAddress; }
    std::string getCustomerPhone() const { return customerPhone; }

    // Setters
    void setCustomerName(const std::string& name) { customerName = name; }
    void setCustomerAddress(const std::string& address) { customerAddress = address; }
    void setCustomerPhone(const std::string& phone) { customerPhone = phone; }
};

#endif // ITEM_H

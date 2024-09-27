// itemmanager.h

#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <vector>
#include <iostream>
#include "item.h"

class ItemManager {
private:
    std::vector<Item> items;

public:
    // Add a new item to the inventory
    void addItem(const Item& item) {
        items.push_back(item);
    }

    // Remove an item by its ID
    void removeItem(int itemID) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getItemID() == itemID) {
                items.erase(it);
                break;
            }
        }
    }

    // Find an item by its ID
    Item* findItem(int itemID) {
        for (auto& item : items) {
            if (item.getItemID() == itemID) {
                return &item;
            }
        }
        return nullptr; // Return nullptr if item not found
    }

    // Display all items in the inventory
    void displayItems() const {
        for (const auto& item : items) {
            std::cout << "Item ID: " << item.getItemID() 
                      << ", Customer Name: " << item.getCustomerName()
                      << ", Customer Address: " << item.getCustomerAddress()
                      << ", Customer Phone: " << item.getCustomerPhone()
                      << std::endl;
        }
    }
};

#endif // ITEMMANAGER_H

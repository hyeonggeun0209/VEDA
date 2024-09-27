// Warehouse.h

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include "ItemManager.h"

class Warehouse {
private:
    int warehouseID;
    std::string location;
    ItemManager itemManager;

public:
    // Constructor
    Warehouse(int id, const std::string& loc) : warehouseID(id), location(loc) {}

    // Getters
    int getWarehouseID() const { return warehouseID; }
    std::string getLocation() const { return location; }

    // Methods to manage items in the warehouse
    void addItem(const Item& item) {
        itemManager.addItem(item);
    }

    void removeItem(int itemID) {
        itemManager.removeItem(itemID);
    }

    Item* findItem(int itemID) {
        return itemManager.findItem(itemID);
    }

    void displayInventory() const {
        itemManager.displayItems();
    }
};

#endif // WAREHOUSE_H

// WarehouseManager.h

#ifndef WAREHOUSEMANAGER_H
#define WAREHOUSEMANAGER_H

#include <vector>
#include "Warehouse.h"

class WarehouseManager {
private:
    std::vector<Warehouse> warehouses;

public:
    // Add a new warehouse
    void addWarehouse(const Warehouse& warehouse) {
        warehouses.push_back(warehouse);
    }

    // Remove a warehouse by its ID
    void removeWarehouse(int warehouseID) {
        for (auto it = warehouses.begin(); it != warehouses.end(); ++it) {
            if (it->getWarehouseID() == warehouseID) {
                warehouses.erase(it);
                break;
            }
        }
    }

    // Find a warehouse by its ID
    Warehouse* findWarehouse(int warehouseID) {
        for (auto& warehouse : warehouses) {
            if (warehouse.getWarehouseID() == warehouseID) {
                return &warehouse;
            }
        }
        return nullptr; // Return nullptr if warehouse not found
    }

    // Display all warehouses
    void displayWarehouses() const {
        for (const auto& warehouse : warehouses) {
            std::cout << "Warehouse ID: " << warehouse.getWarehouseID() 
                      << ", Location: " << warehouse.getLocation() << std::endl;
            warehouse.displayInventory();
        }
    }
};

#endif // WAREHOUSEMANAGER_H

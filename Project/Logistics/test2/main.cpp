// main.cpp

#include <iostream>
#include "item.h"
#include "itemManager.h"

int main() {
    ItemManager manager;

    // Create and add items
    Item item1(1, "John Doe", "123 Elm St", "555-1234");
    Item item2(2, "Jane Smith", "456 Oak St", "555-5678");

    manager.addItem(item1);
    manager.addItem(item2);

    // Display all items
    manager.displayItems();

    // Find and remove an item
    Item* foundItem = manager.findItem(1);
    if (foundItem) {
        std::cout << "Found item with ID 1: " << foundItem->getCustomerName() << std::endl;
    }

    manager.removeItem(1);

    // Display all items after removal
    manager.displayItems();

    return 0;
}

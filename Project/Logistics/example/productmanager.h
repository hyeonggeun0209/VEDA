#ifndef __PRODUCT_MANAGER_H__
#define __PRODUCT_MANAGER_H__

#include <map>
#include <vector>
#include "product.h"
#include "dockmanager.h"
class DockManager;
using namespace std;

class ProductManager {
    public:
        ProductManager();
        ~ProductManager();

        void inputProduct(const string& name, const string& price);
        void addProduct(Product*);
        void receiveProduct(DockManager& dm);
        void deleteProduct(int);
        void modifyProduct(int);
        Product* search(int);
        int getsize();
        int makeId();
        void displayInfo();
        vector<string> parseCSV(istream&, char);

    private:
        map<int, Product*> productList; 

};

#endif    // __PRODUCT_MANAGER_H__

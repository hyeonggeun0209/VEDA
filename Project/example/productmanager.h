#ifndef __PRODUCT_MANAGER_H__
#define __PRODUCT_MANAGER_H__

#include <map>
#include <vector>
#include "product.h"
#include "stockmanager.h"
using namespace std;

class ProductManager {
    public:
        ProductManager();
        ~ProductManager();

        void inputProduct();
        void addProduct(Product*);

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

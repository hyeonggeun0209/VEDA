#ifndef __STOCK_MANAGER_H__
#define __STOCK_MANAGER_H__

#include <map>
#include <vector>
#include "stock.h"

using namespace std;

class StockManager {
  public:
      StockManager();
      ~StockManager();

      void inputStock( );
      void deleteStock(int);
      void modifyStock(int);
      Stock* search(int);
      int makeId();
      void displayInfo();
      vector<string> parseCSV(istream&, char);

      bool displayMenu();

  private:
      map<int, Stock*> StockList;
};

#endif    // __STOCK_MANAGER_H__

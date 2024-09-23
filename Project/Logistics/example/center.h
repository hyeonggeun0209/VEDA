#ifndef __CENTER_H__
#define __CENTER_H__

#include "productmanager.h"
#include "stockmanager.h"
#include "dockmanager.h"
using namespace std;

class Center {
  public:
      Center(DockManager& dm, ProductManager& pm, StockManager& sm);
      void pauseScreen();
      void displayMainMenu();
      void displayDockMenu();
      void printVEDA();
      void animateBoxFromTruck();
      void animateConveyorAndSorting();
      void displayStockMenu();
      void displayProductMenu();
      void DockManagement();
      void StockManagement();
      void ProductManagement();
      void run();
      void waitdock();
  private:
      ProductManager& pm;
      StockManager& sm;
      DockManager& dm;
};

#endif    // __CENTER_H__

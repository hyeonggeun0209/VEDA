#ifndef __BOX_MANAGER_H__
#define __BOX_MANAGER_H__

#include <map>
#include <vector>
#include "box.h"

using namespace std;

class BoxManager {
  public:
      BoxManager();
      ~BoxManager();

      void inputBox( );
      void addBox(Box*);
      void deleteBox(int);
      void modifyBox(int);
      Box* search(int);
      int makeId();
      void displayInfo();
      vector<string> parseCSV(istream&, char);

      bool displayMenu();

  private:
      map<int, Box*> boxList;
};

#endif    // __BOX_MANAGER_H__

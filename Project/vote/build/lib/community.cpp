#include "community.h"
#include <sys/uio.h>

void community::Community(vector<string> &com) {
        int out = 0;
        int key = 0;

        string ma;
        while (out != 1) {
                cout << endl<< "1 : Writing 2: View the text 3 : Exit" << endl;
                cin >> key;
                switch (key) {
                case 1:
                        system("clear");
                        cout << endl<< "Writing (the last letter : ;)" << endl;
                        cout << endl;
                        getline(cin, ma, ';');
                

                        if (ma == "") {
                                cout << endl<< "You've entered something wrong !!" << endl;
                                break;
                        }
                        else {

                                com.push_back(ma);
                                //if (com.size() == 11) com.erase(com.begin());

                        }
                        break;
                case 2:
                        system("clear");
                        if (com.size() == 0) {
                                cout << endl<< "There is no article registered." << endl;

                        }else if(com.size() > 10) {
                                for (int i = 0; i < 10; i++) 
                                        cout << endl << i + 1 << " :: " << com[com.size() - 10 + i] << endl;
                        }else {
                                for (int i = 0; i < com.size(); i++) cout << endl << i + 1 << " :: " << com[i] << endl;
                        }
                        break;
                case 3:
                        system("clear");
                        out = 1;
                        break;
                default:
                        cout << endl<< "wrong input!" << endl;
                        break;
                }
        }
}

#include "vector_viewer.h"

int vector_viewer::add(vector<viewer> &viewers, string PhoneNumber) {
        viewer *p = new viewer;
        p->set(PhoneNumber, 0, 0);

        viewers.push_back(*p);
        return viewers.size() - 1;
}
void vector_viewer::vote(vector<viewer> &viewers, vector<cast> &cast, int num) {
        string name, yn;
        int key = 1;
        int ch = 0;
        int it;
        while (key) {
                int i = viewers[num].getVotePresence();
                switch (i) {
                case 0:
                        cout << endl<<"Please enter the name of the cast to vote.";
                        cin >> name;
                        for (it = 0; it < cast.size(); it++) {
                                if (cast[it].getname() == name) break;
                        }
                        if (it == cast.size()) {
                                cout << endl<<"We don't have any cast." << endl;
                                key = 0;
                                break;

                        }
                        cout <<endl<< "Would you like to vote? [Y/N] ";
                        cin >> yn;
                        if (yn == "y" || yn == "Y") {
                                viewers[num].vote(0, name);
                                for (int it = 0; it < cast.size(); it++) {
                                        if (cast[it].getname() == name) cast[it].addvote();
                                }
                                cout << endl<<"It was voted normally." << endl;
                                key = 0;
                                break;
                        }
                        else if (yn == "n" || yn == "N") {
                                cout << endl<<"It wasn't voted." << endl;
                                key = 0;
                                break;
                        }
                        else {
                                cout << endl<<"Invalid input." << endl;
                                break;
                        }
                case 1:
                        cout << endl<< "Please enter the name of the cast to vote.";
                        cin >> name;
                        for (it = 0; it < cast.size(); it++) {
                                if (cast[it].getname() == name) break;
                        }
                        if (it == cast.size()) {
                                cout << endl<< "We don't have any cast." << endl;
                                key = 0;
                                break;

                        }
                        cout << endl<< "Would you like to vote? [Y/N].";
                        cin >> yn;
                        if (yn == "y" || yn == "Y") {
                                viewers[num].vote(1, name);
                                for (int it = 0; it < cast.size(); it++) {
                                        if (cast[it].getname() == name) cast[it].addvote();
                                }
                                cout << endl<< "It was voted normally." << endl;
                                key = 0;
                                break;
                        }
                        else {
                                key = 0;
                                break;
                        }
                        break;
                case 2:
                        cout << endl<< "You can't vote anymore." << endl;
                        key = 0;
                        break;
                default:
                        break;
                }
        }
}

void vector_viewer::donation(vector<viewer> &viewers, int num, int money) {
        viewers[num].donate(money);
}

void vector_viewer::v_show(vector<viewer> &viewers, int num) {
        cout << endl<< "Cell phonenumber : " << viewers[num].getNumber() << " the number of votes cast : " << viewers[num].getVotePresence() << endl << " voting person : " << viewers[num].getName() << " sponsored amount : " << viewers[num].getDonation() << endl;
}

int vector_viewer::check(vector<viewer> &viewers, string PhoneNumber) {
        int i = 0;
        for (i = 0; i < viewers.size(); i++) {
                if (viewers[i].getNumber() == PhoneNumber) {
                        return i;
                }
        }
        if (i == viewers.size()) {
                return -1;
        }
}
void vector_viewer::show(vector<cast> cast) {
        if (cast.size() == 0) cout << endl<< "There is no registered casts." << endl;
        else{
                cout << endl;       
                for (int it = 0; it < cast.size(); it++) {
                        cout << cast[it].getname() << " : votes -> " << cast[it].getvote() << " ranks -> " << cast[it].getrank() << endl;
                }
        }
}
void vector_viewer::addmy_star(vector<viewer> &viewers, vector<cast> &casts, int num) {
        string names[3];
        string name;
        int a = 0;
        int j = 0;
        int star = 0;
        int ky = 0;
        char keystr;
        int t=0;
        cout << endl<< " ====== Pick 3 stars! ====== " << endl << "!! Once selected star cannot be changed. !!" << endl;
        while (star != 1) {
                cout << endl<< " 1: Registering Your Star 2: See your own star 3: Go to the previous screen. " << endl;
                cin >> ky;
                a = 0;
                switch (ky) {
                case 1:
                        if(casts.size() == 0 ){
                                cout << "The cast already exists." << endl;
                                break;
                        }
                        
                        if (viewers[num].getmystar().size() == 3) {
                                cout << endl<< "All already registered !!" << endl;
                                break;
                        }
                        cout << endl<< "Please enter one by one." << endl;
                        cin >> name;
                        for (int i = 0; i < 3; i++) {
                                if (names[i] == name) {
                                        cout << "The cast already exists." << endl;
                                        a++;
                                        break;
                                }

                        }
                        if (a != 0) break;
                        for (t = 0; t < casts.size(); t++) {
                                if (casts[t].getname() == name) {
                                        cout << endl<< "Should I register " << name << "? (y or n) " << endl;
                                        cin >> keystr;
                                        if (keystr == 'y' || keystr == 'Y') {
                                                cout <<endl<< "Registered!!" << endl;
                                                viewers[num].getmystar().push_back(name);
                                                names[j++] = name;
                                                break;
                                        }
                                        else if (keystr == 'n' || keystr == 'N') {
                                                cout <<endl<< "Please choose someone else!!" << endl;
                                                break;

                                        }
                                        else {
                                                cout << endl<<"You've entered something wrong !!" << endl;
                                                break;
                                        }
                                }
                        }      
                        if (t == casts.size()) cout << endl<< "You've entered something wrong !!" << endl; 


                        break;
                case 2:

                        for (int it = 0; it < casts.size(); it++)
                                for (int i = 0; i < viewers[num].getmystar().size(); i++)
                                        if (viewers[num].getmystar()[i] == casts[it].getname()) cout << casts[it].getname() << ' ' << casts[it].getage() << ' ' << casts[it].getEntertainment() << endl;
                        break;
                case 3:
                        star = 1;
                        break;
                default:
                        cout << endl<< "wrong input!" << endl;
                        break;
                }


         }
       
}

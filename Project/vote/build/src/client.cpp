#define _POSIX_C_SOURCE 199309L
#include <iostream>
#include <string>
#include <vector>
#include <signal.h>
#include "common.h"
#include "community.h"
using namespace std;

int main() {
    int server_fd = open_fifo(SERVER_FIFO_NAME, O_WRONLY);
    int client_fd = 0;

    data_t buf;
    buf.c_pid = getpid();

    pid_t s_pid;
    memset(buf.data, 0, sizeof(buf.data));

    char client_fifo[256];
    sprintf(client_fifo, CLIENT_FIFO_NAME, buf.c_pid);
    make_fifo(client_fifo);
    int money;
    int read_bytes = 0;
    string name;
    int key, key1;
    int out = 1;
    int size;
    int vote_num = 0;
    string num;
    string str(buf.data);
    community d;
    vector<string> vs, v;
    int end_vote;
    int key2 = 0; int key3 = 0; int key0 = 0;
    int ok = 0;
    vector<string> st;
    int a = 0;
    int j = 0;
    int star = 0;
    int ky = 0; 
    char keystr;
    int t = 0;
    
    cout << "Please enter your cell phone number." << endl; // client's phonenumber send!
    cin >> num;
    strcpy(buf.data, num.c_str()); // string to buf
    write(server_fd, &buf, sizeof(buf));

    client_fd = open(client_fifo, O_RDONLY); // server's pid get!
    if (client_fd != -1) {
        read_bytes = read(client_fd, &buf, sizeof(buf));
        s_pid = buf.c_pid;
        close(client_fd);
    }
    sigval s;
    system("clear");
    while(out) {
        cout << "***************************************" << endl;
        cout << endl << "1: Voting" << '\t' << "5: View Rank" << endl << "2: Sponsoring" << '\t' << "6 : community" << endl << "3: See my Info" << '\t' << "7 : To predict" << endl << "4: Show cast" << '\t' << "8 : Predictive Results" << endl << "9 : voting result" << '\t' << "10 : quit" << endl;
        cin >> key;
        key1 = key;
        system("clear");
        switch (key) {
            case 1:
                system("clear"); 
                sigqueue(s_pid, SIGUSR1, s);
                write(server_fd, &key1, sizeof(int));

                client_fd = open(client_fifo, O_RDONLY);
                read(client_fd, &end_vote, sizeof(int));

                if (end_vote == 1) {
                    cout << endl<< "end_vote!" << endl;
                    break;
                }

                read(client_fd, &size, sizeof(int));
                if(size == 0 ){
                    cout << endl << "You can't vote yet";
                    cout << endl;
                    break;
                }   

                close(client_fd);
                if(vote_num == 2){
                    cout << "Exceeded number of votes" << endl;
                    break;
                }

                vote_num++;
                cout << "enter your pick" << endl;
                cin >> name;
                strcpy(buf.data, name.c_str());
                write(server_fd, &buf, sizeof(buf));
                break;

            case 2:
                system("clear");
                sigqueue(s_pid, SIGUSR1, s);
                write(server_fd, &key1, sizeof(int));
                client_fd = open(client_fifo, O_RDONLY);
                read(client_fd, &end_vote, sizeof(int));

                if (end_vote == 1) {
                    cout << endl<< "end_vote!" << endl;
                    break;
                }
                close(client_fd);
            
                cout << "enter donation you want" << endl;
                cin >> money;
                write(server_fd, &money, sizeof(int));
                client_fd = open(client_fifo, O_RDONLY);
                read(client_fd, &buf, sizeof(buf));
                str = buf.data;
                cout << str << endl;
                close(client_fd);
                break;

            case 3:
                system("clear");
                sigqueue(s_pid, SIGUSR1, s);
                write(server_fd, &key1, sizeof(int));

                cout << "show my info" << endl;
                write(server_fd, &key, sizeof(int));
                client_fd = open(client_fifo, O_RDONLY);
                read(client_fd, &buf, sizeof(buf));
                str = buf.data;
                cout << "phonenum votenum votecast donation" << endl;
                cout << str << endl;     
                close(client_fd);
                break;

            case 4:
                system("clear");
                sigqueue(s_pid, SIGUSR1, s);
                write(server_fd, &key1, sizeof(int));

                cout << "show all casts" << endl;
                client_fd = open(client_fifo, O_RDONLY);
                read(client_fd, &size, sizeof(int));
                cout << size << " casts "<< endl << endl;
                for(int i = 0; i < size; i++) {
                    read(client_fd, &buf, sizeof(buf));
                    str = buf.data;
                    cout << str << endl;
                }
                close(client_fd);
                break;

            case 5:
                system("clear");
                sigqueue(s_pid, SIGUSR1, s);
                write(server_fd, &key1, sizeof(int));

                cout << "show rank" << endl;
                client_fd = open(client_fifo, O_RDONLY);
                read(client_fd, &size, sizeof(int));
                cout << size << " casts "<< endl << endl;
                for(int i = 0; i < size; i++) {
                    read(client_fd, &buf, sizeof(buf));
                    str = buf.data;
                    cout << str << endl;
                }
                close(client_fd);
                break;

            case 6:
                system("clear");
                sigqueue(s_pid, SIGUSR1, s);
                write(server_fd, &key1, sizeof(int));

                client_fd = open(client_fifo, O_RDONLY);
                read(client_fd, &key2, sizeof(int));

                key0 = key2 - key3;

                for(int i = key3; i < key2; i++) {
                    read(client_fd, &buf, sizeof(buf));
                    str = buf.data;
                    v.push_back(str);
                }
                close(client_fd);

                d.Community(v);
                cout << endl;

                key3 = v.size();
                write(server_fd, &key3, sizeof(int));
                for(int i = key2; i < key3; i++) {
                    strcpy(buf.data, v[i].c_str());
                    write(server_fd, &buf, sizeof(buf));
                }

                break;

            case 7:
                system("clear");
                sigqueue(s_pid, SIGUSR1, s);
                write(server_fd, &key1, sizeof(int));

                client_fd = open(client_fifo, O_RDONLY);
                read(client_fd, &end_vote, sizeof(int));

                if (end_vote == 1) {
                    cout << endl<< "end_vote!" << endl;
                    break;
                }
                read(client_fd, &ok, sizeof(int));
                if(ok == 0) {
                    cout << "need more money" << endl;
                    break;
                } else {
                    cout << "you can enjoy it!" << endl << endl;
                }

                read(client_fd, &buf, sizeof(buf));
                str = buf.data;
                cout << str << endl;
                read(client_fd, &buf, sizeof(buf));
                str = buf.data;
                cout << str << endl;

                read(client_fd, &size, sizeof(int));
                
                
                while (star != 1) {
                    cout << endl<< " 1: Registering Your Star 2: See your own star 3: Go to the previous screen. " << endl;
                    cin >> ky;
                    a = 0;
                    switch (ky) {
                        case 1:
                            system("clear");
                            if (st.size() == 3) {
                                cout << endl<< "All already registered !!" << endl;
                                break;
                            }
                            cout << endl<< "Please enter one by one." << endl;

                            for(int i = 0; i < 3; i++) {
                                cin >> name;
                                st.push_back(name);
                            }

                         break;
                        case 2:
                            system("clear");
                            for (int i = 0; i < st.size(); i++)
                                cout <<  st[i] << endl;
                                break;
                        case 3:
                            system("clear");
                            star = 1;
                            break;
                         default:
                            cout << endl<< "wrong input!" << endl;
                            break;
                }

            }  
                break;

            case 8:
                system("clear");
                sigqueue(s_pid, SIGUSR1, s);
                write(server_fd, &key1, sizeof(int));

                for(int j = 0; j < 3; j++) {
                    strcpy(buf.data, st[j].c_str());
                    write(server_fd, &buf, sizeof(buf));
                }

                read(client_fd, &buf, sizeof(buf));
                str = buf.data;
                cout << str << endl;

                break;

            case 9:
                system("clear");
                sigqueue(s_pid, SIGUSR1, s);
                write(server_fd, &key1, sizeof(int));

                client_fd = open(client_fifo, O_RDONLY);
                read(client_fd, &end_vote, sizeof(int));

                if (end_vote == 0) {
                    cout << endl<< "Voting is in progress." << endl;
                    break;
                }

                close(client_fd);
                cout << "voting result" << endl;
                client_fd = open(client_fifo, O_RDONLY);
                read(client_fd, &size, sizeof(int));
                cout << size << " casts "<< endl << endl;
                for(int i = 0; i < size; i++) {
                    read(client_fd, &buf, sizeof(buf));
                    str = buf.data;
                    cout << str << endl;
                }
                close(client_fd);
                break;

            case 10:
                out = 0;
                break;
            
             default:
                cout << endl<< "Wrong input!" << endl;
                break;
        } 
    }     

    close(server_fd);
    unlink(client_fifo);

    return 0;
}
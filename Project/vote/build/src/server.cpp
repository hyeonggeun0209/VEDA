#include "common.h"
#include "vector_cast.h"
#include "vector_viewer.h"
#include "community.h"


data_t buf;
int server_fd = 0;
int client_fd = 0;
char client_fifo[256];
pid_t c_pid, s_pid;
vector_cast ca;
vector<cast> c;
vector<cast> debut;
vector_viewer va;
vector<viewer> v;
string str(buf.data);
int id = 0;
string strage;
string all;
int money;
int vote_num = 0;
int key1;
int dona;
int key0 = 0; int key2 = 0; int key3 = 0;
community d;
vector<string> vs;
int end_vote = 0;
int m;
int predic = 0;
int ok = 0;
int admin_mode = false;   //initialization
void sig_handler(int sig){
    admin_mode = true;
}
vector<string> st;
string name;
int a = 0;
int j = 0;
int star = 0;
int ky = 0;
char keystr;
int t=0;

void sigusr1(int sig) {
    read(server_fd, &key1, sizeof(int));
    int size = 0;
    string comment;
    string vall;
    string vpre;
    string vdon;
    string strage;
    string all;
    string vote;
    string rank;

    switch (key1) {
        case 1:
            client_fd = open(client_fifo, O_WRONLY);
            write(client_fd, &end_vote, sizeof(int));
            
            if (end_vote == 1) {
                cout << endl<< "end_vote!" << endl;
                break;
            }

            size = c.size();
            write(client_fd, &size, sizeof(int));
            
            if(c.size() == 0 ){
                break;
            
            }
            close(client_fd);
            read(server_fd, &buf, sizeof(buf));
            str = buf.data;
            cout << str << endl;
            ca.vote(c, str);
            v[id].vote(v[id].getVotePresence(), str);
            break;

        case 2:
            client_fd = open(client_fifo, O_WRONLY);
            write(client_fd, &end_vote, sizeof(int));
            if (end_vote == 1) {
                cout << endl<< "end_vote!" << endl;
                break;
            }
            close(client_fd);

            read(server_fd, &dona, sizeof(int));
            va.donation(v, id, dona);
            for(int i = 0, money = 0; i < v.size(); i++) {
                money+=v[i].getDonation();
            }
            comment = "Thanks for your support";

            client_fd = open(client_fifo, O_WRONLY);
            strcpy(buf.data, comment.c_str());
            write(client_fd, &buf, sizeof(buf));
            close(client_fd);
            break;

        case 3:
            client_fd = open(client_fifo, O_WRONLY); // open client fifo (WRONLY)
            vpre = to_string(v[id].getVotePresence());
            vdon = to_string(v[id].getDonation());
            vall = v[id].getNumber() + ' ' + vpre + ' ' + v[id].getName() + ' ' + vdon;
            client_fd = open(client_fifo, O_WRONLY);
            strcpy(buf.data,vall.c_str());
            write(client_fd, &buf, sizeof(buf));
            close(client_fd);
            break;

        case 4:
            client_fd = open(client_fifo, O_WRONLY); // open client fifo (WRONLY)
            size = c.size();
            write(client_fd, &size, sizeof(int));
            for(int i = 0; i<size; i++) {
                strage = to_string(c[i].getage());
                all = c[i].getname() + ' ' + strage + ' ' + c[i].getEntertainment();
                strcpy(buf.data,all.c_str());
                write(client_fd, &buf, sizeof(buf));
            }
            close(client_fd); 
            break;

        case 5:
            ca.sort(c);
            client_fd = open(client_fifo, O_WRONLY); // open client fifo (WRONLY)
            size = c.size();
            write(client_fd, &size, sizeof(int));
            for(int i = 0; i<size; i++) {
                strage = to_string(c[i].getage());
                vote = to_string(c[i].getvote());
                rank = to_string(c[i].getrank());
                all = c[i].getname() + ' ' + strage + ' ' + c[i].getEntertainment() + ' ' + vote + ' ' + rank;
                strcpy(buf.data,all.c_str());
                write(client_fd, &buf, sizeof(buf));
            }
            close(client_fd);
            break;

        case 6:
            client_fd = open(client_fifo, O_WRONLY);
            key0 = vs.size();
            write(client_fd, &key0, sizeof(int));

            for (int i = key2; i < key0; i++) {
                strcpy(buf.data, vs[i].c_str());
                write(client_fd, &buf, sizeof(buf));
            }
            close(client_fd);

            read(server_fd, &key2, sizeof(int));
            key3 = key2 - key0;
            for(int i = key0; i < key2; i++) {
                read(server_fd, &buf, sizeof(buf));
                str = buf.data;
                vs.push_back(str);
            }
            break;

        case 7:
            client_fd = open(client_fifo, O_WRONLY);
            write(client_fd, &end_vote, sizeof(int));
            if (end_vote == 1) {
                cout << endl<< "end_vote!" << endl;
                break;
            }
            if(v[id].getDonation() < 5000) {
                ok = 0;
                write(client_fd, &ok, sizeof(int));
                break;
            } else {
                ok = 1;
                write(client_fd, &ok, sizeof(int));
                
            }
            
            
            str = "======== Pick 3 stars! ======== ";
            strcpy(buf.data, str.c_str());
            write(client_fd, &buf, sizeof(buf));
            str = "!! Once selected star cannot be changed. !!";
            strcpy(buf.data, str.c_str());
            write(client_fd, &buf, sizeof(buf));

            size = c.size();
            write(client_fd, &size, sizeof(int));
            break;
            
            

        case 8:
            if(end_vote == 0){
                cout << endl<< "Voting is in progress. " << endl;
                break;
            }
            for(int i = 0; i< 3; i++) {
                read(server_fd, &buf, sizeof(buf));
                str = buf.data;
                st.push_back(str);
            }
            m = 0;
            if (st.size() == 3) {
                for (int p = 0; p < 3; p++) {
                    for (int j = 0; j < 3; j++) {
                        if (st[p] == debut[j].getname()) {
                                m++;
                        }
                    }
                }
                if (m == 3) {

                    str = "You've made a good prediction!! ";
                    strcpy(buf.data, str.c_str());
                    write(client_fd, &buf, sizeof(buf));
                
                    break;
                }else if(m == 2 || m == 1 || m ==0){
                    str = "that's too bad,,,,";
                    strcpy(buf.data, str.c_str());
                    write(client_fd, &buf, sizeof(buf));
                }                         
            }else {
                str = "You didn't make your debut group.";
                strcpy(buf.data, str.c_str());
                write(client_fd, &buf, sizeof(buf));
                break;
            }
            cout << endl;
            break;
        
        case 9:
            client_fd = open(client_fifo, O_WRONLY);
            write(client_fd, &end_vote, sizeof(int));
            if (end_vote == 0) {
                break;
            }
            close(client_fd);
            ca.sort(c);
            client_fd = open(client_fifo, O_WRONLY); // open client fifo (WRONLY)
            size = c.size();
            write(client_fd, &size, sizeof(int));
            for(int i = 0; i<size; i++) {
                strage = to_string(c[i].getage());
                vote = to_string(c[i].getvote());
                rank = to_string(c[i].getrank());
                all = c[i].getname() + ' ' + strage + ' ' + c[i].getEntertainment() + ' ' + vote + ' ' + rank;
                strcpy(buf.data,all.c_str());
                write(client_fd, &buf, sizeof(buf));
            }
            close(client_fd);
            break;
    }
    admin_mode = true;
}


int main() {
    make_fifo(SERVER_FIFO_NAME);
    server_fd = open_fifo(SERVER_FIFO_NAME, O_RDONLY);
    cout << "Client connected" << endl;

    int read_bytes = 0;
    char *ptr = 0;
    string str(buf.data);
    string name;
    int age;
    string ent;
    int key, key1;
    int out = 1;
    int out1 = 1;
    int num;
    int size;
    string strage;
    string vall;
    string vpre;
    string vdon;

    struct sigaction action;

    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    action.sa_handler = sigusr1;
    if (sigaction(SIGUSR1, &action, NULL) == -1) { 
        perror("sigusr: sigaction");
        _exit(0);
        
    }
    signal(SIGINT, sig_handler);

    read_bytes = read(server_fd, &buf, sizeof(buf));
    c_pid = buf.c_pid;
    str = buf.data;
    system("clear");
    cout << str << " client " << endl;
    id = va.check(v, str);
    if (id == -1) id = va.add(v, str);

    sprintf(client_fifo, CLIENT_FIFO_NAME, c_pid);
    client_fd = open(client_fifo, O_WRONLY); // open client fifo (WRONLY)
    buf.c_pid = getpid();
    if (client_fd != -1) {
        write(client_fd, &buf, sizeof(buf));
        close(client_fd);
    }

    while(out) {
        //if (admin_mode == true) {
        cout << "********************************************" << endl;
        cout << endl<< "1 : Add cast" << '\t' << "6 : View Rank" << endl << "2 : Delete cast" << '\t' << "7 : End voting" << endl << "3 : Modify cast" << '\t' << "8 : View voting results" << endl << "4 : Show cast" << '\t' << "9 : Community" << endl << "5 : wait" << '\t' << "10: voting" << endl << "11: Exit" << endl;
        cin >> key;
        system("clear");
        switch (key) {
            case 1:
                cout << endl<< "Please enter name, age, entertainment" << endl;
                cin >> name >> age >> ent;
                ca.cast_add(c, name, age, ent);
                system("clear");
                break;
            case 2:
                cout << endl<< "Enter the name of the person you want to delete" << endl;
                cin >> name;
                ca.cast_delete(c,name);
                system("clear");
                break;
            case 3:
                cout << endl<< "Enter the name of the person you want to modify" << endl;
                cin >> name;
                ca.cast_modify(c, name);
                system("clear");
                break;

            case 4:
                system("clear");
                ca.show(c);
                break;
            case 5:
                system("clear");
                admin_mode = false;
                cout << "waiting client input" << endl;
                while(admin_mode == false);
                break;
           
            case 6:
                system("clear");
                ca.sort(c);
                ca.show(c);
                break;

            case 7:
                system("clear");
                if(c.size() < 3){
                    cout << endl << "Could not end voting" << endl;
                     break;
                }
                
                ca.end_vote(c, end_vote);
                for (int q = 0; q < 3; q++) debut.push_back(c[q]);
                    cout << endl<< "debut group ";
                    cout << endl;
                    for (int q = 0; q < 3; q++) {
                        cout << debut[q].getname() << " ";
                    }
                cout << endl;
                break;

            case 8:
                system("clear");
                if (end_vote == 0) {
                    cout << endl<< "Voting is in progress." << endl;;
                    break;
                }
                ca.show_vote(c);
                cout << endl;
                break;

            case 9:
                system("clear");
                d.Community(vs);
                cout << endl;
                break;

            case 10:
                system("clear");
                if (end_vote == 1) {
                    cout << endl<< "end_vote!" << endl;
                    break;
                }
                if(c.size() == 0 ){
                    cout << endl << "You can't vote yet";
                    cout << endl;
                    break;
                }
                if(vote_num == 2){
                    cout << "Exceeded number of votes" << endl;
                    break;
                }
                vote_num++;
                cout << "enter your pick" << endl;
                cin >> name;
                ca.vote(c, name);
                break;

            case 11:
                out = 0;
                break;

            default:
                cout << endl<< "Wrong input!" << endl;
                break;
        
        }
    }
    close(server_fd);
    unlink(SERVER_FIFO_NAME);

    return 0;
}
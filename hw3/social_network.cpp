#include "network.h"
#include <iostream>
#include <sstream>
#include <assert.h>
using namespace std;

int main(int argc, char *argv[]){
    Network n;

    if (argc > 1) n.readUsers(argv[1]);
    if (argc > 2) n.readPosts(argv[2]);

    std::cout << "1. Add user\n";
    std::cout << "2. Add connection\n";
    std::cout << "3. Delete connection\n";
    std::cout << "4. Write to file\n";
    std::cout << "Other: Exit\n";

    string command;
    while (true)
    {   
        std::cout << "> ";
        getline(cin, command);
        istringstream ss(command);

        int option;
        ss >> option;
        if (ss.fail()) {
            cout << "input error" << endl;
            continue;
        }

        switch (option)
        {
        // add user
        // 1 id firstname lastname year zip
        case 1: {
            int id, year, zip;
            string fname, lname;
            ss >> id >> fname >> lname >> year >> zip;
            if (ss.fail()){
                cout << "input error" << endl;
                break;
            }
            User * u = new User(id, fname+" "+lname, year, zip, {});
            n.addUser(u);
            break;
        }

        // add connection
        // 2 name1 name2
        case 2:{
            string name [4];
            ss >> name[0] >> name[1] >> name[2] >> name[3];
            if (ss.fail()){
                cout << "input error" << endl;
                break;
            }
            if(n.addConnection(name[0]+" "+name[1], name[2]+" "+name[3]) == -1)
                cout << "function error" << endl;
            break;
        }
        
        // detele connection
        // 3 name1 name2
        case 3:{
            string name [4];
            ss >> name[0] >> name[1] >> name[2] >> name[3];
            if (ss.fail()){
                cout << "input error" << endl;
                break;
            }
            if(n.deleteConnection(name[0]+" "+name[1], name[2]+" "+name[3])==-1)
                cout << "function error" << endl;
            break;
        }

        // write users
        // 4 filename
        case 4:{
            char* file;
            ss >> file;
            if (ss.fail()){
                cout << "input error" << endl;
                break;
            }
            if(n.writeUsers(file) == -1) cout << "function error" << endl;
            break;
        }

        case 5: {
            string fname, lname;
            int howMany;
            ss >> fname >> lname >> howMany;
            if (ss.fail()) {
                cout << "input error" << endl;
                break;
            }
            string fullname = fname + " " + lname;
            int id = n.getId(fullname);
            if (id == -1) {
                cout << "user not found" << endl;
                break;
            }
            string result = n.getPostsString(id, howMany, false);
            cout << result;
            break;
        }

        // unknown input, exit
        default:
            exit(0);
            break;
        }
    }
    return 0;
}
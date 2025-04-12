#include"network.h"
#include<fstream>
#include<sstream>
#include<limits>

Network::Network(){
    users_={};
}

bool Network::userExists(std::string name){
    return names_.count(name) != 0;
}

void Network::addUser(User* u){
    std::string name = u->getName();
    if(!userExists(name)){
        users_.push_back(u);
        names_.insert(name);
    }
}

int Network::addConnection(std::string s1, std::string s2){
    if (s1 == s2) return -1;
    if (!userExists(s1) || !userExists(s2)) return -1;
    User* u1 = nullptr;
    User* u2 = nullptr;
    for (auto user : users_){
        if (user->getName() == s1) u1 = user;
        if (user->getName() == s2) u2 = user;
    }
    u1->addFriend(u2->getId());
    u2->addFriend(u1->getId());
    return 0;
}

int Network::deleteConnection(std::string s1, std::string s2){
    if (s1 == s2) return -1;
    if (!userExists(s1) || !userExists(s2)) return -1;
    User* u1 = nullptr;
    User* u2 = nullptr;
    for (auto user : users_){
        if (user->getName() == s1) u1 = user;
        if (user->getName() == s2) u2 = user;
    }
    u1->deleteFriend(u2->getId());
    u2->deleteFriend(u1->getId());
    return 0;
}

int Network::getId(std::string name){
    if (!userExists(name)) return -1;
    for (auto user : users_){
        if (user->getName() == name) return user->getId();
    }
    return -1;
}

// file name
int Network::readUsers(char* fname){
    std::ifstream file(fname);
    if(!file) return -1;

    int id, year, zip;

    file>>id; // start from numbers of users
    while(file>>id){
        std::string name, fn, ln;
        file >> fn >> ln; // read first name + last name
        name = fn + " " + ln;
        file >> year >> zip;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // move to the next line

        std::string line;
        getline(file, line);
        std::stringstream ss(line);
        std::set<int> friends;
        int i; // ids
        while(ss>>i){
            friends.insert(i);
        }

        User * u = new User(id, name, year, zip, friends);
        addUser(u);
    }
    return 0;
}

// file name
int Network::writeUsers(char* fname){
    std::ofstream file(fname);
    file << numUsers() << "\n";
    for(auto user : users_){
        file << user->getId() << "\n";
        file << "\t" << user->getName() << "\n";
        file << "\t" << user->getYear() << "\n";
        file << "\t" << user->getZip() << "\n" << "\t";

        const std::set<int> & friends = user->getFriends();
        for (int id : friends){
            file << id << " ";
        }
        file << "\n";
    }
    return 0;
}

User* Network::getUser(int id){
    for (auto user : users_){
        if (user->getId() == id) return user;
    }
    return nullptr;
}
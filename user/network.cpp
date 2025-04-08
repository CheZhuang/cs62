#include"network.h"

Network::Network(){
    users_={};
}

bool Network::userExists(std::string name){
    return names_.count(name) != 0;
}

void Network::addUser(User* u){
    std::string name = u->getName();
    if(users_.empty() || !userExists(name)){
        users_.push_back(u);
        names_.insert(name);
    }
}

int Network::addConnection(std::string s1, std::string s2){
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
}
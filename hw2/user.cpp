#include "user.h"

User::User() {
    id_= -1;
    name_= "";
    year_= -1;
    zip_= -1;
    friends_= {};
}

User::User(int i, std::string n, int y, int z, std::set<int> f)
: id_(i), name_(n), year_(y), zip_(z), friends_(std::move(f)) {}

void User::addFriend(int id){
    friends_.insert(id); // avoid duplictaes
}

void User::deleteFriend(int id){
    friends_.erase(id);
}


#include "user.h"

User::User() {
    id_= -1;
    name_= "";
    year_= -1;
    zip_= -1;
    friends_= {};
    messages_ = {};
}

User::User(int i, std::string n, int y, int z, std::set<int> f)
: id_(i), name_(n), year_(y), zip_(z), friends_(std::move(f)), messages_({}) {}

void User::addFriend(int id){
    friends_.insert(id); // avoid duplictaes
}

void User::deleteFriend(int id){
    friends_.erase(id);
}

void User::addPost(Post* p){
    if (p==nullptr) return;
    messages_.push_back(p);
}

std::string User::getPostsString(int howMany, bool showOnlyPublic){
    std::string result = "";
    size_t i = messages_.size();
    while(i > 0 && howMany != 0){
        i--;
        if (showOnlyPublic && !messages_[i]->getIsPublic()){
            continue;
        }
        result += messages_[i]->toString()+"\n\n";
        howMany--;
    }
    return result;
}
#ifndef USER_H
#define USER_H

#include<string>
#include<set>

class User {
    private:
        int id_;
        std::string name_;
        int year_;
        int zip_;
        std::set<int> friends_;

    public:
        User();
        User(int i, std::string n, int y, int z, std::set<int> f);
        void addFriend(int id);
        void deleteFriend(int id);
        int getId() { return id_; }
        std::string getName() { return name_; }
        int getYear() { return year_; }
        int getZip() { return zip_; }
        std::set<int> & getFriends() { return friends_; }
};

#endif
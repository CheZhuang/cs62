#ifndef USER_H
#define USER_H

class User {
    private:
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends;

    public:
    User();
    void addFriend(int id);
    void deleteFriend(int id);
    int getId() { return id_; }
    std::string getName() { return name_; }
    int getYear() { return year_; }
    int getZip() { return zip_; }
    std::set<int> getfriends { return friends; }
};

#endif
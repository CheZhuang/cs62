#ifndef NETWORK_H
#define NETWORk_H

#include<vector>
#include"user.cpp"

class Network
{
private:
    std::vector<User*> users_;
    std::set<std::string> names_; // prevent duplicates

public:
    Network();
    void addUser(User* u);
    int addConnection(std::string s1, std::string s2);
    int deleteConnection(std::string s1, std::string s2);
    int getId(std::string name);
    int readUsers(char* fname);
    int writeUsers(char* fname);
    int numUsers() { return users_.size(); }
    User* getUser(int id);
    bool userExists(std::string name);
};

#endif
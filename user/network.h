#ifndef NETWORK_H
#define NETWORK_H

#include<vector>
#include"user.h"

class Network
{
private:
    std::vector<User*> users_; 
    std::set<std::string> names_; // track existence, fast
    
public:
    // prve: none
    // post: creates an empty Network object
    Network();

    // prve: u must be a non-null pointer to a valid User object;
    //       the user's name must not already exist in the network
    // post: u is added to users_ and its name is recorded in names_
    void addUser(User* u);

    // prve: s1 and s2 must refer to two distinct existing users
    // post: if valid, user s1 and user s2 become friends (bidirectionally);
    //       returns 0 on success, -1 on failure
    int addConnection(std::string s1, std::string s2);

    // prve: s1 and s2 must refer to two distinct existing users
    // post: if valid, the friendship between s1 and s2 is removed;
    //       returns 0 on success, -1 on failure
    int deleteConnection(std::string s1, std::string s2);

    // prve: name must correspond to a valid user in the network
    // post: returns the user's id if found, or -1 otherwise
    int getId(std::string name);

    // prve: fname is a valid path to a file containing user data in expected format
    // post: loads users from the file into the network;
    //       returns 0 on success, -1 if file cannot be opened
    int readUsers(char* fname);

    // prve: fname is a valid writable file path
    // post: writes all user data in correct format to the file;
    //       returns 0 on success, -1 if file cannot be written
    int writeUsers(char* fname);

    // prve: none
    // post: returns the number of users currently in the network
    int numUsers() { return users_.size(); }

    // prve: id must be in the valid range of existing user ids
    // post: returns a pointer to the User with the given id, or nullptr if not found
    User* getUser(int id);

    // prve: none
    // post: returns true if name exists in the network, false otherwise
    bool userExists(std::string name);

    // destructor
    // prve: none
    // post: deletes all User objects in users_ and frees memory
    ~Network() {
        for (User* user : users_)
            delete user;
    }
};


#endif
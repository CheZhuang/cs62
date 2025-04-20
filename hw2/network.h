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

    // prve: id must be in the valid range of existing user IDs
    // post: returns a pointer to the User with the given id, or nullptr if not found
    User* getUser(int id);

    // prve: none
    // post: returns true if a user with the given name exists in the network, false otherwise
    bool userExists(std::string name);

    // prve: none
    // post: returns true if a user with the given ID exists in the network, false otherwise
    bool userExists(int id);

    // prve: 'from' and 'to' must be valid user IDs in the network
    // post: returns a vector of user IDs representing the shortest path from 'from' to 'to'; returns empty vector if no path exists
    std::vector<int> shortestPath(int from, int to);

    // prve: 'from' must be a valid user ID; 'distance' must be >= 1
    // post: finds and returns a path to a user at exactly the given distance from 'from'; sets 'to' to the ID of that user; if no such user is found, returns an empty vector and sets 'to' to -1
    std::vector<int> distanceUser(int from, int &to, int distance);

    // prve: 'who' must be a valid user ID
    // post: returns a list of suggested friends who are two degrees away and share the most mutual friends; sets 'score' to the number of mutual friends; returns empty vector and score = -1 if no suggestions
    std::vector<int> suggestFriends(int who, int &score);

    // prve: id1 and id2 must be valid user IDs
    // post: returns the number of mutual friends shared between the two users; returns -1 if either user is not found
    int getCommonFriends(int id1, int id2);

    // prve: none
    // post: returns a list of all connected components in the network; each component is represented as a list of user IDs
    std::vector<std::vector<int>> groups();

    // destructor
    // prve: none
    // post: deletes all User objects in users_ and frees memory
    ~Network() {
        for (User* user : users_)
            delete user;
    }
};


#endif
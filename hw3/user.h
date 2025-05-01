#ifndef USER_H
#define USER_H

#include<string>
#include<set>
#include<vector>
#include"post.h"

class User {
    private:
        int id_;
        std::string name_;
        int year_;
        int zip_;
        std::set<int> friends_;
        std::vector<Post*> messages_;

        public:
        // prve: none
        // post: creates a default-initialized User object (fields uninitialized)
        User();
    
        // prve: none
        // post: creates a User with the given id, name, year, zip, and friends list
        User(int i, std::string n, int y, int z, std::set<int> f);
    
        // prve: id must be a valid user ID and not already in friends_
        // post: id is added to the user's friends_ set
        void addFriend(int id);
    
        // prve: id must be in the user's friends_ set
        // post: id is removed from the user's friends_ set if present
        void deleteFriend(int id);

        void addPost(Post* p);

        std::string getPostsString(int howMany, bool showOnlyPublic);
    
        // prve: none
        // post: returns the user's unique ID
        int getId() const { return id_; }
    
        // prve: none
        // post: returns the user's name
        std::string getName() const { return name_; }
    
        // prve: none
        // post: returns the user's birth year
        int getYear() const { return year_; }
    
        // prve: none
        // post: returns the user's ZIP code
        int getZip() const { return zip_; }
    
        // prve: none
        // post: returns a reference to the user's friends_ set
        std::set<int> & getFriends() { return friends_; }

        // prve: none
        // post: returns a reference to the user's messages_ vector
        std::vector<Post*> & getPosts() { return messages_; }
    };
#endif
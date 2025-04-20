#include "network.h"
#include <fstream>
#include <sstream>
#include <limits>
#include <queue>
#include <algorithm>
#include <stack>

Network::Network(){
    users_={};
}

bool Network::userExists(std::string name){
    return names_.count(name) != 0;
}

bool Network::userExists(int id){
    return id < numUsers();
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
    if (!userExists(id)) return nullptr;
    for (auto user : users_){
        if (user->getId() == id) return user;
    }
    return nullptr;   
}

std::vector<int> Network::shortestPath(int from, int to){
    std::vector<int> path;
    User* start = getUser(from);
    User* target = getUser(to);
    // if from & to exist
    if (start==nullptr || target==nullptr){
        return path;
    }

    std::queue<User*> q;
    std::vector<bool> visited(numUsers(), false);
    std::vector<int> previous(numUsers(), -1);
    q.push(start);
    visited[from] = true;
    // BFS
    while(!q.empty()){
        User* current = q.front();
        if (current == target) break;
        for (int id : current->getFriends()){
            if (!visited[id]){
                visited[id] = true;
                q.push(getUser(id));
                previous[id] = current->getId();
            }
        }
        q.pop();
    }

    if (!visited[to]){
        return path;
    }

    int i = to;
    while(i != -1){
        path.push_back(i);
        i = previous[i];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> Network::distanceUser(int from, int & to, int distance){
    to = -1;
    User* start = getUser(from);
    if (start == nullptr) return{};

    std::queue<User*> q;
    q.push(start);
    std::vector<int> distances(numUsers(), -1);
    distances[from] = 0;

    while (!q.empty() && distances[q.front()->getId()] < distance){
        User* current = q.front();
        for (int id : current->getFriends()){
            if (distances[id] == -1){
                distances[id] = distances[current->getId()] + 1;
                // immediately return if found
                if(distances[id] == distance){
                    to = id;
                    return shortestPath(from, to);
                }
                q.push(getUser(id));
            }
        }
        q.pop();
    }
    return{};
}

int Network::getCommonFriends(int id1, int id2){
    User* u1 = getUser(id1);
    User* u2 = getUser(id2);
    if (u1==nullptr || u2==nullptr) return -1;

    const std::set<int> & f1 = u1->getFriends();
    const std::set<int> & f2 = u2->getFriends();

    std::set<int> comb(f1.begin(), f1.end());
    comb.insert(f2.begin(), f2.end());

    return f1.size() + f2.size() - comb.size(); // calculate the deleted duplicate elements
}

std::vector<int> Network::suggestFriends(int who, int & score){
    User* start = getUser(who);
    if (start == nullptr) return{};

    const int DISTANCE = 2; // distance of strong connections
    std::vector<int> suggestions;
    std::vector<int> commonFriends(numUsers(), -1);
    std::queue<User*> q;
    q.push(start);
    std::vector<int> distances(numUsers(), -1);
    distances[who] = 0;

    while (!q.empty() && distances[q.front()->getId()] < DISTANCE){
        User* current = q.front();
        for (int id : current->getFriends()){
            if (distances[id] == -1){
                distances[id] = distances[current->getId()] + 1;

                if(distances[id] == DISTANCE){
                    suggestions.push_back(id);
                    commonFriends[id] = getCommonFriends(who, id);
                }
                q.push(getUser(id));
            }
        }
        q.pop();
    }
    
    score = *std::max_element(commonFriends.begin(), commonFriends.end());
    for (auto it = suggestions.begin(); it != suggestions.end();){
        if (commonFriends[*it] != score){
            it = suggestions.erase(it);
        }else{
            ++it;
        }
    }
    return suggestions;
}

std::vector<std::vector<int>> Network::groups(){
    std::vector<std::vector<int>> result;
    std::vector<bool> visited(numUsers(), false);

    for (int i=0; i<numUsers(); i++){
        if (visited[i]) continue;

        std::vector<int> component;
        std::stack<int> s;
        s.push(i);
        visited[i] = true;

        while (!s.empty()){
            int current = s.top();
            s.pop();
            component.push_back(current);

            User* user = getUser(current);
            for (int neighbor : user->getFriends()){
                if (!visited[neighbor]){
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }

        result.push_back(component);
    }

    return result;
}
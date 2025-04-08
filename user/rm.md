- Glasp使用适当的 User 方法编写 user.h 和 user.cpp 文件。编写每个方法时，用一个小的主程序进行测试。确保它不仅能编译和运行，还能针对各种输入给出您期望的输出。

- 在 Gradescope 上提交您的 user.h 和 user.cpp 文件，查看它们是否通过测试。修复所有错误。

- 编写 network.h 和 network.cpp 文件来实现添加用户的方法。编写每个方法时，用一个小的主程序进行测试。确保它不仅能编译和运行，还能针对各种输入给出您期望的输出。

- 编写一个简单的主程序来实现菜单系统，但只包含添加用户、打印所有用户以及退出的选项。

- 继续逐个添加网络类的方法（添加好友连接、删除好友连接、打印用户的所有好友），并在菜单系统中实现该选项，在继续下一个之前单独测试每个方法。

- 最后，实现文件 I/O 功能，以便从文件读取数据库或将其写回到文件。使用stringstreams 和 getline(istream, string) 函数来解析数据库文件可能会有所帮助。

- 运行您的程序。您可以手动输入菜单选项来测试程序的某些功能。

- 确保所有命令均能正常工作，并且您可以将更新后的数据库写入新文件。检查该文件以确保其格式和数据正确。尝试在程序的新运行中加载它。 

```
Network
+ Network()
+ addUser(User*) : void
+ addConnection(string s1, string s2) : int
+ deleteConnection(string s1, string s2) : int
+ getId(string name) : int
+ readUsers(char* fname) : int
+ writeUsers(char *fname) : int
+ numUsers() : int
+ getUser(int id): user*
- users_:vector<User*> 
```

- A vector of Users (you should store pointers to dynamically allocated User objects). 
The Network class should support the following operations:

- You must define a default (no-argument) constructor.

- A getUser method that takes in an ID and returns a pointer to the corresponding User. In the case there is no user with that id, this should return a nullptr.

- An addUser method to add a User to the Network database. This method should accept a pointer to a User object.

- An addConnection method accepting two strings (format: first name + last name separated by a space in between) corresponding to the names of the Users to make friends. Return 0 on success, -1 if either of the users are invalid. We will not attempt to create a self-connection (from user1 to user1).

- A deleteConnection method accepting two strings (format: first name + last name separated by a space in between) of the names of Users to delete friend connections. Return 0 on success, -1 if either of the users are invalid.

- A getId method accepting a user name and returning the corresponding ID for that user, or -1 otherwise. 

- A numUsers method that returns the number of Users in the Network

- A readUsers method that initializes all of the network’s information from a file. This method should accept a char * (c string) indicating the name of the file to read the users from and return 0 on success, -1 on failure. (EDIT: I realized the return value is a bit confusing. It's okay if you always return 0. The original intention was that you return -1 if the file open fails.)

- A writeUsers method that writes all of the network’s information to a file. This method should accept a char * (c string) indicating the name of the file to write the users to and return 0 on success, -1 on failure. (EDIT: Like readUsers, it's okay if you always return 0.)

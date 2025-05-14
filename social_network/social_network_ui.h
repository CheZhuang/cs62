#ifndef SOCIAL_NETWORK_UI_H
#define SOCIAL_NETWORK_UI_H
#include <QMainWindow>
#include <QTableWidgetItem>
#include "network.h"

class User;

QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkUI;
}
QT_END_NAMESPACE

class SocialNetworkUI : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkUI(QWidget *parent = nullptr);
    ~SocialNetworkUI();
    // initial network_
    void networkInit();
    // refresh the widget
    void display();
    // detrmine if login
    void login();
    // go back to my profile
    void goBack();
    // add a friend
    void addFriend();
    // submit a post
    void submitPost();
    // refresh friends table
    void printFriends();
    // refresh suggest friends table
    void printSuggestFriends();
    // refresh post browser
    void printPosts();
    // change current page after cliking item
    void changeCurrent(int row);

private:
    Ui::SocialNetworkUI *ui;
    Network network_;
    User* user_;
    User* currentAt_;
};
#endif // SOCIAL_NETWORK_UI_H

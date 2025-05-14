#include "social_network_ui.h"
#include "./ui_social_network_ui.h"

SocialNetworkUI::SocialNetworkUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkUI)
{
    networkInit();

    ui->setupUi(this);
    ui->profileWidget->setVisible(false);
    ui->suggestTable->setColumnCount(2);
    ui->suggestTable->setHorizontalHeaderLabels({"ID", "Name"});
    ui->friendsTable->setColumnCount(2);
    ui->friendsTable->setHorizontalHeaderLabels({"ID", "Name"});

    connect(ui->loginButton, &QPushButton::clicked, this, &SocialNetworkUI::login);
    connect(ui->backButton, &QPushButton::clicked, this, &SocialNetworkUI::goBack);
    connect(ui->followButton, &QPushButton::clicked, this, &SocialNetworkUI::addFriend);
    connect(ui->postButton, &QPushButton::clicked, this, &SocialNetworkUI::submitPost);
    connect(ui->friendsTable, &QTableWidget::itemClicked, this, [&](QTableWidgetItem *item) {
        int row = item->row();
        int id = ui->friendsTable->item(row, 0)->text().toInt();
        this->changeCurrent(id);
    });
    connect(ui->suggestTable, &QTableWidget::itemClicked, this, [&](QTableWidgetItem *item) {
        int row = item->row();
        int id = ui->suggestTable->item(row, 0)->text().toInt();
        this->changeCurrent(id);
    });
}

void SocialNetworkUI::changeCurrent(int id) {
    currentAt_ = network_.getUser(id);
    display();
}

void SocialNetworkUI::networkInit() {
    network_ = Network();
    std::string file = "users.txt";
    network_.readUsers(file.c_str());
    file = "posts.txt";
    network_.readPosts(file.c_str());
}

SocialNetworkUI::~SocialNetworkUI() {
    delete ui;
}

void SocialNetworkUI::login() {
    std::string name = ui->loginEdit->toPlainText().toStdString();
    int id = network_.getId(name);

    if (id == -1) {
        ui->loginLable->setText("Invalid name");
        return;
    }

    user_ = network_.getUser(id);
    currentAt_ = user_;
    ui->loginWidget->setVisible(false);
    display();
}

void SocialNetworkUI::goBack() {
    currentAt_ = user_;
    display();
}

void SocialNetworkUI::addFriend() {
    network_.addConnection(user_->getName(), currentAt_->getName());
    network_.writeUsers("users.txt");
    printFriends();
}

void SocialNetworkUI::submitPost() {
    Post* p;
    std::string content = ui->postEdit->toPlainText().toStdString();
    bool isIncoming = currentAt_ != user_;
    network_.addPost(currentAt_->getId(), content, 0, isIncoming, user_->getName(), true);

    network_.writePosts("posts.txt");
    printPosts();
}

void SocialNetworkUI::display() {
    if (user_ == nullptr || currentAt_ == nullptr) return;
    bool inMyProfile = user_==currentAt_;

    std::string header = (inMyProfile) ? "My Profile" : (currentAt_->getName()+"’s Profile");
    ui->headerLable->setText(QString::fromStdString(header));

    if (inMyProfile) {
        printSuggestFriends();
        ui->suggestTable->setVisible(true);
    } else {
        ui->suggestTable->setVisible(false);
    }
    printFriends();
    printPosts();
    if (!ui->profileWidget->isVisible()) ui->profileWidget->setVisible(true);
}

void SocialNetworkUI::printFriends() {
    std::set<int> friends = currentAt_->getFriends();
    ui->friendsTable->setRowCount(friends.size());

    int i=0;
    for (int id : friends) {
        User* u = network_.getUser(id);
        QString name = QString::fromStdString(u->getName());
        ui->friendsTable->setItem(i, 0, new QTableWidgetItem(QString::number(id)));
        ui->friendsTable->setItem(i++, 1, new QTableWidgetItem(name));
    }
}

void SocialNetworkUI::printSuggestFriends() {
    int score = 0;
    std::vector<int> friends = network_.suggestFriends(user_->getId(), score);
    ui->suggestTable->setRowCount(friends.size());

    int i=0;
    for (int id : friends) {
        User* u = network_.getUser(id);
        QString name = QString::fromStdString(u->getName());
        ui->suggestTable->setItem(i, 0, new QTableWidgetItem(QString::number(id)));
        ui->suggestTable->setItem(i++, 1, new QTableWidgetItem(name));
    }
}

void SocialNetworkUI::printPosts() {
    ui->postBrowser->clear();
    bool showOnlyPublic = user_ != currentAt_;
    std::string posts = currentAt_->getPostsString(5, showOnlyPublic);
    ui->postBrowser->append(QString::fromStdString(posts));
}

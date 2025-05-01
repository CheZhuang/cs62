#ifndef POST_H
#define POST_H

#include <string>

class Post
{
private:
    int messageId_;
    int ownerId_;
    std::string message_;
    int likes_;

public:
    Post() : messageId_(0), ownerId_(0), message_(""), likes_(0) {}
    Post(int messageId, int ownerId, std::string message, int likes) : 
        messageId_(messageId), ownerId_(ownerId), message_(message), likes_(likes) {}
    virtual std::string toString();
    int getMessageId() { return messageId_; }
    int getOwnerId() { return ownerId_; }
    std::string getMessage() { return message_; }
    int getLikes() { return likes_; }
    virtual std::string getAuthor() { return ""; }
    virtual bool getIsPublic() { return true; }
};

class IncomingPost : public Post
{
private:
    std::string author_;
    bool isPublic_;

public:
    IncomingPost() : Post(), author_(""), isPublic_(false) {}
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author): 
        Post(messageId, ownerId, message, likes), isPublic_(isPublic), author_(author) {}
    std::string toString() override;
    std::string getAuthor() override { return author_; }
    bool getIsPublic() override { return isPublic_; }
};

#endif
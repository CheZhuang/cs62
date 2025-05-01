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
    // prve: none
    // post: returns a formatted string describing the post content and number of likes
    virtual std::string toString();

    // prve: none
    // post: returns the unique ID of the post
    int getMessageId() { return messageId_; }

    // prve: none
    // post: returns the ID of the user who owns this post
    int getOwnerId() { return ownerId_; }

    // prve: none
    // post: returns the textual content of the post
    std::string getMessage() { return message_; }

    // prve: none
    // post: returns the number of likes this post has received
    int getLikes() { return likes_; }

    // prve: none
    // post: returns the author name; default is empty string (for owner posts)
    virtual std::string getAuthor() { return ""; }

    // prve: none
    // post: returns true if the post is public (default true for owner posts)
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
    std::string toString() override;  // post: returns a formatted string with author, visibility, and content
    std::string getAuthor() override { return author_; } // post: returns the author of the IncomingPost
    bool getIsPublic() override { return isPublic_; } // post: returns the visibility status of the IncomingPost
};

#endif
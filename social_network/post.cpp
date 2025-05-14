#include "post.h"
#include <sstream>

std::string Post::toString() {
    std::stringstream ss;
    ss << message_ << " Liked by " << likes_ << " people";
    return ss.str();
}
std::string IncomingPost::toString() {
    std::string isPublic = isPublic_ ? "" : "(private) ";
    return author_ + " wrote: " + isPublic + this->Post::toString();
}
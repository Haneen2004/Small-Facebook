#ifndef POST_HPP
#define POST_HPP

#pragma once
#include <string>
#include <memory>

class Member;

class Post
{
private:
    int postId{0};
    std::string text;
    int totalLikes{0};
    int totalShares{0};
    std::shared_ptr<Member> owner;

public:
    Post() = default;
    Post(int id, std::string txt, std::shared_ptr<Member> author)
        : postId(id), text(std::move(txt)), owner(std::move(author)) {}

    int getPostId() const { return postId; }
    std::string getText() const { return text; }
    int getTotalLikes() const { return totalLikes; }
    int getTotalShares() const { return totalShares; }
    std::shared_ptr<Member> getOwner() const { return owner; }
};

#endif

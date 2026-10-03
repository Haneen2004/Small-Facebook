#ifndef POST_HPP
#define POST_HPP

#pragma once
#include <string>
#include <memory>
using namespace std;

class Member;

class Post
{
private:
    int postId{0};
    string text;
    int totalLikes{0};
    int totalShares{0};
    shared_ptr<Member> owner;

public:
    Post() = default;
    Post(int id, string txt, shared_ptr<Member> author)
        : postId(id), text(move(txt)), owner(move(author)) {}

    int getPostId() const { return postId; }
    string getText() const { return text; }
    int getTotalLikes() const { return totalLikes; }
    int getTotalShares() const { return totalShares; }
    shared_ptr<Member> getOwner() const { return owner; }
};

#endif
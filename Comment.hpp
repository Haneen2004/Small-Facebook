#ifndef COMMENT_HPP
#define COMMENT_HPP

#pragma once
#include <string>
#include <memory>
using namespace std;

class Member;

class Comment
{
private:
    int commentId{0};
    string text;
    int totalLikes{0};
    shared_ptr<Member> owner;

public:
    Comment() = default;

    int getCommentId() const { return commentId; }
    string getText() const { return text; }
    int getTotalLikes() const { return totalLikes; }
    shared_ptr<Member> getOwner() const { return owner; }
};

#endif
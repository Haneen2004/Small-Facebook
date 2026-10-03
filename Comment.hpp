#ifndef COMMENT_HPP
#define COMMENT_HPP

#pragma once
#include <string>
#include <memory>

class Member;

class Comment
{
private:
    int commentId{0};
    std::string text;
    int totalLikes{0};
    std::shared_ptr<Member> owner;

public:
    Comment() = default;

    int getCommentId() const { return commentId; }
    std::string getText() const { return text; }
    int getTotalLikes() const { return totalLikes; }
    std::shared_ptr<Member> getOwner() const { return owner; }
};

#endif

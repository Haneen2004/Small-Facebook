#ifndef SEARCH_HPP
#define SEARCH_HPP

#pragma once
#include <string>
#include <vector>
#include <memory>

class Member;
class Group;
class Page;
class Post;

class Search
{
public:
    virtual ~Search() = default;
    virtual std::vector<std::shared_ptr<Member>> searchMember(const std::string &name) = 0;
    virtual std::vector<std::shared_ptr<Group>> searchGroup(const std::string &name) = 0;
    virtual std::vector<std::shared_ptr<Page>> searchPage(const std::string &name) = 0;
    virtual std::vector<std::shared_ptr<Post>> searchPost(const std::string &word) = 0;
};

#endif

#ifndef SEARCH_HPP
#define SEARCH_HPP

#pragma once
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Member;
class Group;
class Page;
class Post;

class Search
{
public:
    virtual ~Search() = default;
    virtual vector<shared_ptr<Member>> searchMember(const string &name) = 0;
    virtual vector<shared_ptr<Group>> searchGroup(const string &name) = 0;
    virtual vector<shared_ptr<Page>> searchPage(const string &name) = 0;
    virtual vector<shared_ptr<Post>> searchPost(const string &word) = 0;
};

#endif
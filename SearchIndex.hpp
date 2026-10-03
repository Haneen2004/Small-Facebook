#ifndef SEARCH_INDEX_HPP
#define SEARCH_INDEX_HPP

#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "Search.hpp"
#include "Member.hpp"
#include "Group.hpp"
#include "Page.hpp"
#include "Post.hpp"

class SearchIndex : public Search
{
private:
    unordered_map<string, vector<shared_ptr<Member>>> memberNames;
    unordered_map<string, vector<shared_ptr<Group>>> groupNames;
    unordered_map<string, vector<shared_ptr<Page>>> pageTitles;
    unordered_map<string, vector<shared_ptr<Post>>> posts;

public:
    bool addMember(const shared_ptr<Member> &member)
    {
        if (member)
        {
            memberNames[member->getName()].push_back(member);
            return true;
        }
        return false;
    }

    bool addGroup(const shared_ptr<Group> &group)
    {
        if (group)
        {
            groupNames[group->getName()].push_back(group);
            return true;
        }
        return false;
    }

    bool addPage(const shared_ptr<Page> &page)
    {
        if (page)
        {
            pageTitles[page->getName()].push_back(page);
            return true;
        }
        return false;
    }

    bool addPost(const shared_ptr<Post> &post)
    {
        if (post)
        {
            posts[post->getText()].push_back(post);
            return true;
        }
        return false;
    }

    vector<shared_ptr<Member>> searchMember(const string &name) override
    {
        auto it = memberNames.find(name);
        if (it != memberNames.end())
        {
            return it->second;
        }
        return {};
    }

    vector<shared_ptr<Group>> searchGroup(const string &name) override
    {
        auto it = groupNames.find(name);
        if (it != groupNames.end())
        {
            return it->second;
        }
        return {};
    }

    vector<shared_ptr<Page>> searchPage(const string &title) override
    {
        auto it = pageTitles.find(title);
        if (it != pageTitles.end())
        {
            return it->second;
        }
        return {};
    }

    vector<shared_ptr<Post>> searchPost(const string &word) override
    {
        auto it = posts.find(word);
        if (it != posts.end())
        {
            return it->second;
        }
        return {};
    }
};

#endif
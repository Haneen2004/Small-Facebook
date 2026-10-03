#ifndef GROUP_HPP
#define GROUP_HPP

#pragma once
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Member;

class Group
{
private:
    int groupId{0};
    string name;
    string description;
    int totalMembers{0};
    vector<shared_ptr<Member>> members;

public:
    Group() = default;
    Group(int id, string n) : groupId(id), name(move(n)) {}

    bool addMember(const shared_ptr<Member> &member)
    {
        members.push_back(member);
        totalMembers = static_cast<int>(members.size());
        return true;
    }

    bool updateDescription(const string &desc)
    {
        description = desc;
        return true;
    }

    int getGroupId() const { return groupId; }
    string getName() const { return name; }
    string getDescription() const { return description; }
};

#endif
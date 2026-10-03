#ifndef GROUP_HPP
#define GROUP_HPP

#pragma once
#include <string>
#include <vector>
#include <memory>

class Member;

class Group
{
private:
    int groupId{0};
    std::string name;
    std::string description;
    int totalMembers{0};
    std::vector<std::shared_ptr<Member>> members;

public:
    Group() = default;
    Group(int id, std::string n) : groupId(id), name(std::move(n)) {}

    bool addMember(const std::shared_ptr<Member> &member)
    {
        members.push_back(member);
        totalMembers = static_cast<int>(members.size());
        return true;
    }

    bool updateDescription(const std::string &desc)
    {
        description = desc;
        return true;
    }

    int getGroupId() const { return groupId; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
};

#endif

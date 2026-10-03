#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <memory>
#include "Person.hpp"
#include "Profile.hpp"
#include "Post.hpp"
#include "Message.hpp"
#include "ConnectionInvitation.hpp"

class Member : public Person, public enable_shared_from_this<Member>
{
private:
    int memberId{0};
    time_t dateOfMembership{time(nullptr)};
    Profile profile;

    unordered_set<int> memberFollows;
    unordered_set<int> memberConnections;
    unordered_set<int> pageFollows;
    unordered_set<int> memberSuggestions;
    unordered_set<int> connectionInvitations;
    unordered_set<int> groupFollows;

    // 1. Graph in-memory representation of the social network
    inline static unordered_map<int, unordered_set<int>> networkGraph;

    // 2. In-memory registry of all members for quick access
    inline static unordered_map<int, shared_ptr<Member>> memberRegistry;

public:
    Member() = default;
    explicit Member(int id) : memberId(id) {}

    int getMemberId() const { return memberId; }
    void setMemberId(int id) { memberId = id; }

    // Retrieve a member by ID from the in-memory registry
    static shared_ptr<Member> getMemberById(int id)
    {
        auto it = memberRegistry.find(id);
        if (it != memberRegistry.end())
        {
            return it->second;
        }
        return nullptr;
    }
    // add a member to the in-memory registry
    static void registerMember(const shared_ptr<Member> &member)
    {
        if (member)
        {
            memberRegistry[member->getMemberId()] = member;
        }
    }

    // retrieve member connections by ID from the in-memory graph
    static unordered_set<int> getMemberConnectionsById(int id)
    {
        auto it = networkGraph.find(id);
        if (it != networkGraph.end())
        {
            return it->second;
        }
        return {};
    }

    // add a bidirectional connection and update the in-memory graph
    void addConnection(int friendId)
    {
        memberConnections.insert(friendId);
        networkGraph[this->memberId].insert(friendId);

        // also add it in the reverse direction
        networkGraph[friendId].insert(this->memberId);
        auto friendIt = memberRegistry.find(friendId);
        if (friendIt != memberRegistry.end())
        {
            friendIt->second->memberConnections.insert(this->memberId);
        }
    }

    const unordered_set<int> &getMemberConnections() const
    {
        return memberConnections;
    }

    // 2-level BFS search for member suggestions based on friends of friends
    vector<pair<int, int>> searchMemberSuggestions()
    {
        unordered_map<int, int> suggestions;

        for (int firstLevelId : memberConnections)
        {
            unordered_set<int> firstLevelConnections = getMemberConnectionsById(firstLevelId);
            for (int firstLevelConnectionId : firstLevelConnections)
            {
                if (firstLevelConnectionId == this->memberId)
                    continue;
                findMemberSuggestion(suggestions, firstLevelConnectionId);

                unordered_set<int> secondLevelConnections = getMemberConnectionsById(firstLevelConnectionId);
                for (int secondLevelConnectionId : secondLevelConnections)
                {
                    if (secondLevelConnectionId == this->memberId)
                        continue;
                    findMemberSuggestion(suggestions, secondLevelConnectionId);
                }
            }
        }

        vector<pair<int, int>> sortedSuggestions(suggestions.begin(), suggestions.end());
        sort(sortedSuggestions.begin(), sortedSuggestions.end(),
             [](const pair<int, int> &a, const pair<int, int> &b)
             {
                 return a.second > b.second;
             });

        return sortedSuggestions;
    }

private:
    void findMemberSuggestion(unordered_map<int, int> &suggestions, int connectionId)
    {
        if (memberConnections.count(connectionId) || connectionInvitations.count(connectionId))
        {
            return;
        }
        suggestions[connectionId]++;
    }
};

#endif
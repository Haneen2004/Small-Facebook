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

class Member : public Person, public std::enable_shared_from_this<Member>
{
private:
    int memberId{0};
    time_t dateOfMembership{time(nullptr)};
    Profile profile;

    std::unordered_set<int> memberFollows;
    std::unordered_set<int> memberConnections;
    std::unordered_set<int> pageFollows;
    std::unordered_set<int> memberSuggestions;
    std::unordered_set<int> connectionInvitations;
    std::unordered_set<int> groupFollows;

    // 1. Graph in-memory representation of the social network
    inline static std::unordered_map<int, std::unordered_set<int>> networkGraph;

    // 2. In-memory registry of all members for quick access
    inline static std::unordered_map<int, std::shared_ptr<Member>> memberRegistry;

public:
    Member() = default;
    explicit Member(int id) : memberId(id) {}

    int getMemberId() const { return memberId; }
    void setMemberId(int id) { memberId = id; }

    // Retrieve a member by ID from the in-memory registry
    static std::shared_ptr<Member> getMemberById(int id)
    {
        auto it = memberRegistry.find(id);
        if (it != memberRegistry.end())
        {
            return it->second;
        }
        return nullptr;
    }
    // add a member to the in-memory registry
    static void registerMember(const std::shared_ptr<Member> &member)
    {
        if (member)
        {
            memberRegistry[member->getMemberId()] = member;
        }
    }

    // retrieve member connections by ID from the in-memory graph
    static std::unordered_set<int> getMemberConnectionsById(int id)
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

    const std::unordered_set<int> &getMemberConnections() const
    {
        return memberConnections;
    }

    std::vector<std::pair<int, int>> searchMemberSuggestions()
    {
        std::unordered_map<int, int> suggestions;

        for (int firstLevelId : memberConnections)
        {
            std::unordered_set<int> firstLevelConnections = getMemberConnectionsById(firstLevelId);
            for (int firstLevelConnectionId : firstLevelConnections)
            {
                if (firstLevelConnectionId == this->memberId)
                    continue;
                findMemberSuggestion(suggestions, firstLevelConnectionId);

                std::unordered_set<int> secondLevelConnections = getMemberConnectionsById(firstLevelConnectionId);
                for (int secondLevelConnectionId : secondLevelConnections)
                {
                    if (secondLevelConnectionId == this->memberId)
                        continue;
                    findMemberSuggestion(suggestions, secondLevelConnectionId);
                }
            }
        }

        std::vector<std::pair<int, int>> sortedSuggestions(suggestions.begin(), suggestions.end());
        std::sort(sortedSuggestions.begin(), sortedSuggestions.end(),
                  [](const std::pair<int, int> &a, const std::pair<int, int> &b)
                  {
                      return a.second > b.second;
                  });

        return sortedSuggestions;
    }

private:
    void findMemberSuggestion(std::unordered_map<int, int> &suggestions, int connectionId)
    {
        if (memberConnections.count(connectionId) || connectionInvitations.count(connectionId))
        {
            return;
        }
        suggestions[connectionId]++;
    }
};

#endif

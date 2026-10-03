#include <cassert>
#include <iostream>
#include <memory>

#include "Member.hpp"
#include "Admin.hpp"
#include "Page.hpp"
#include "SearchIndex.hpp"

void testMemberRegistration()
{
    auto member = std::make_shared<Member>(100);
    member->setName("TestUser");

    Member::registerMember(member);

    auto result = Member::getMemberById(100);

    assert(result != nullptr);
    assert(result->getMemberId() == 100);
    assert(result->getName() == "TestUser");
}

void testBidirectionalConnections()
{
    auto member1 = std::make_shared<Member>(101);
    auto member2 = std::make_shared<Member>(102);

    member1->setName("Alice");
    member2->setName("Bob");

    Member::registerMember(member1);
    Member::registerMember(member2);

    member1->addConnection(102);

    assert(member1->getMemberConnections().count(102) == 1);
    assert(member2->getMemberConnections().count(101) == 1);
}

void testFriendRecommendations()
{
    auto user = std::make_shared<Member>(201);
    auto friend1 = std::make_shared<Member>(202);
    auto friend2 = std::make_shared<Member>(203);
    auto candidate = std::make_shared<Member>(204);

    user->setName("User");
    friend1->setName("Friend1");
    friend2->setName("Friend2");
    candidate->setName("Candidate");

    Member::registerMember(user);
    Member::registerMember(friend1);
    Member::registerMember(friend2);
    Member::registerMember(candidate);

    // User <-> Friend1
    user->addConnection(202);

    // User <-> Friend2
    user->addConnection(203);

    // Friend1 <-> Candidate
    friend1->addConnection(204);

    // Friend2 <-> Candidate
    friend2->addConnection(204);

    auto suggestions = user->searchMemberSuggestions();

    bool foundCandidate = false;
    int candidateCount = 0;

    for (const auto &[memberId, count] : suggestions)
    {
        if (memberId == 204)
        {
            foundCandidate = true;
            candidateCount = count;
        }
    }

    assert(foundCandidate);
    assert(candidateCount >= 2);
}

void testAdminBlockAndUnblock()
{
    auto member = std::make_shared<Member>(301);
    member->setName("AdminTestUser");

    Member::registerMember(member);

    Admin admin("ADMIN-TEST");

    bool blocked = admin.blockUser(301);

    assert(blocked);
    assert(member->getStatus() == AccountStatus::BLACKLISTED);

    bool unblocked = admin.unblockUser(301);

    assert(unblocked);
    assert(member->getStatus() == AccountStatus::ACTIVE);
}

void testPageOperations()
{
    Page page(401, "Test Page");

    assert(page.isActive());

    Admin admin("ADMIN-PAGE");

    bool disabled = admin.disablePage(page);

    assert(disabled);
    assert(!page.isActive());

    bool enabled = admin.enablePage(page);

    assert(enabled);
    assert(page.isActive());
}

void testPasswordReset()
{
    auto member = std::make_shared<Member>(501);

    member->setPassword("OldPassword");

    // Same password should be rejected.
    assert(!member->resetPassword("OldPassword"));

    // Empty password should be rejected.
    assert(!member->resetPassword(""));

    // Different password should be accepted.
    assert(member->resetPassword("NewPassword"));

    assert(member->getPassword() == "NewPassword");
}

void testSearchIndex()
{
    auto member = std::make_shared<Member>(601);
    member->setName("SearchUser");

    SearchIndex searchIndex;

    assert(searchIndex.addMember(member));

    auto results = searchIndex.searchMember("SearchUser");

    assert(results.size() == 1);
    assert(results[0] == member);

    auto emptyResults =
        searchIndex.searchMember("UnknownUser");

    assert(emptyResults.empty());
}

int main()
{
    testMemberRegistration();
    testBidirectionalConnections();
    testFriendRecommendations();
    testAdminBlockAndUnblock();
    testPageOperations();
    testPasswordReset();
    testSearchIndex();

    std::cout << "All tests passed.\n";

    return 0;
}
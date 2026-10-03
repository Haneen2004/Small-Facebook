#include <iostream>
#include <memory>
#include <vector>
#include "Member.hpp"
#include "Admin.hpp"
#include "Page.hpp"

int main()
{
    cout << "=========================\n";
    cout << "   Small Facebook  \n";
    cout << "=========================\n\n";

    // 1. create members and set their names
    auto m1 = make_shared<Member>(1);
    m1->setName("Ahmed");
    auto m2 = make_shared<Member>(2);
    m2->setName("Mona");
    auto m3 = make_shared<Member>(3);
    m3->setName("Ali");
    auto m4 = make_shared<Member>(4);
    m4->setName("Sara");
    auto m5 = make_shared<Member>(5);
    m5->setName("Omar");

    // 2. Register members in the in-memory registry
    Member::registerMember(m1);
    Member::registerMember(m2);
    Member::registerMember(m3);
    Member::registerMember(m4);
    Member::registerMember(m5);

    // 3. create the friendship network (Bidirectional Connections)
    // Ahmed (1) <-> Mona (2) & Ali (3)
    m1->addConnection(2);
    m1->addConnection(3);

    // Mona (2) <-> Sara (4) & Omar (5)
    m2->addConnection(4);
    m2->addConnection(5);

    // Ali (3) <-> Omar (5)
    m3->addConnection(5);

    // 4. Test the friend suggestion algorithm (2-Level BFS) for Ahmed
    cout << "--- 1. Testing Connection Suggestions ---\n";
    cout << "Target User: " << m1->getName() << " (ID: " << m1->getMemberId() << ")\n";

    auto suggestions = m1->searchMemberSuggestions();

    if (suggestions.empty())
    {
        cout << "No suggestions found.\n";
    }
    else
    {
        cout << "Suggested Member ID | Mutual Connections Count\n";
        cout << "--------------------|-------------------------\n";
        for (const auto &[memberId, count] : suggestions)
        {
            cout << "         " << memberId << "          |            " << count << "\n";
        }
    }
    cout << "\n";

    // 5. Test Admin operations: block/unblock a member and enable/disable a page
    cout << "--- 2. Testing Admin Operations ---\n";
    Admin admin("ADM-001");
    admin.setName("Admin User");

    cout << "Initial Status of Member 4 (Sara): "
         << (m4->getStatus() == AccountStatus::ACTIVE ? "ACTIVE" : "OTHER") << "\n";

    // block the member
    admin.blockUser(4);
    cout << "Status of Member 4 after Admin Block: "
         << (m4->getStatus() == AccountStatus::BLACKLISTED ? "BLACKLISTED" : "OTHER") << "\n";

    // unblock the member
    admin.unblockUser(4);
    cout << "Status of Member 4 after Admin Unblock: "
         << (m4->getStatus() == AccountStatus::ACTIVE ? "ACTIVE" : "OTHER") << "\n\n";

    // 6. Test page management
    Page techPage(101, "Tech World");
    cout << "Page status initially active: " << (techPage.isActive() ? "YES" : "NO") << "\n";

    admin.disablePage(techPage);
    cout << "Page status after Admin disable: " << (techPage.isActive() ? "YES" : "NO") << "\n\n";

    // 7. Test password reset logic
    cout << "--- 3. Testing Password Reset Logic ---\n";
    m1->setPassword("OldPass123");
    cout << "Setting new password 'OldPass123': "
         << (m1->resetPassword("OldPass123") ? "Success" : "Failed (Same as old)") << "\n";

    cout << "Setting new password 'NewPass456': "
         << (m1->resetPassword("NewPass456") ? "Success" : "Failed") << "\n";

    return 0;
}
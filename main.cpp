#include <iostream>
#include <memory>

#include "Member.hpp"
#include "Admin.hpp"
#include "Page.hpp"

void setupMembers(
    std::shared_ptr<Member> &m1,
    std::shared_ptr<Member> &m2,
    std::shared_ptr<Member> &m3,
    std::shared_ptr<Member> &m4,
    std::shared_ptr<Member> &m5)
{
     m1 = std::make_shared<Member>(1);
     m1->setName("Ahmed");

     m2 = std::make_shared<Member>(2);
     m2->setName("Mona");

     m3 = std::make_shared<Member>(3);
     m3->setName("Ali");

     m4 = std::make_shared<Member>(4);
     m4->setName("Sara");

     m5 = std::make_shared<Member>(5);
     m5->setName("Omar");

     Member::registerMember(m1);
     Member::registerMember(m2);
     Member::registerMember(m3);
     Member::registerMember(m4);
     Member::registerMember(m5);
}

void setupConnections(
    const std::shared_ptr<Member> &m1,
    const std::shared_ptr<Member> &m2,
    const std::shared_ptr<Member> &m3)
{
     // Ahmed <-> Mona
     m1->addConnection(2);

     // Ahmed <-> Ali
     m1->addConnection(3);

     // Mona <-> Sara
     m2->addConnection(4);

     // Mona <-> Omar
     m2->addConnection(5);

     // Ali <-> Omar
     m3->addConnection(5);
}

void demonstrateRecommendations(const std::shared_ptr<Member> &member)
{
     std::cout << "--- 1. Connection Suggestions ---\n";

     std::cout << "Target User: "
               << member->getName()
               << " (ID: "
               << member->getMemberId()
               << ")\n\n";

     auto suggestions = member->searchMemberSuggestions();

     if (suggestions.empty())
     {
          std::cout << "No suggestions found.\n\n";
          return;
     }

     std::cout << "Suggested Member ID | Mutual Connections Count\n";
     std::cout << "--------------------|-------------------------\n";

     for (const auto &[memberId, count] : suggestions)
     {
          std::cout << "         "
                    << memberId
                    << "          |            "
                    << count
                    << '\n';
     }

     std::cout << '\n';
}

void demonstrateAdminOperations(
    const std::shared_ptr<Member> &member)
{
     std::cout << "--- 2. Admin Operations ---\n";

     Admin admin("ADM-001");
     admin.setName("Admin User");

     std::cout << "Initial status of member "
               << member->getMemberId()
               << ": "
               << (member->getStatus() == AccountStatus::ACTIVE
                       ? "ACTIVE"
                       : "OTHER")
               << '\n';

     admin.blockUser(member->getMemberId());

     std::cout << "After blocking: "
               << (member->getStatus() == AccountStatus::BLACKLISTED
                       ? "BLACKLISTED"
                       : "OTHER")
               << '\n';

     admin.unblockUser(member->getMemberId());

     std::cout << "After unblocking: "
               << (member->getStatus() == AccountStatus::ACTIVE
                       ? "ACTIVE"
                       : "OTHER")
               << "\n\n";

     Page techPage(101, "Tech World");

     std::cout << "Page active initially: "
               << (techPage.isActive() ? "YES" : "NO")
               << '\n';

     admin.disablePage(techPage);

     std::cout << "Page active after disable: "
               << (techPage.isActive() ? "YES" : "NO")
               << "\n\n";
}

void demonstratePasswordReset(
    const std::shared_ptr<Member> &member)
{
     std::cout << "--- 3. Password Reset ---\n";

     member->setPassword("OldPass123");

     bool samePassword =
         member->resetPassword("OldPass123");

     std::cout << "Reset using the same password: "
               << (samePassword ? "Success" : "Rejected")
               << '\n';

     bool newPassword =
         member->resetPassword("NewPass456");

     std::cout << "Reset using a new password: "
               << (newPassword ? "Success" : "Failed")
               << "\n\n";
}

int main()
{
     std::cout << "=========================\n";
     std::cout << "      Small Facebook\n";
     std::cout << "=========================\n\n";

     std::shared_ptr<Member> m1;
     std::shared_ptr<Member> m2;
     std::shared_ptr<Member> m3;
     std::shared_ptr<Member> m4;
     std::shared_ptr<Member> m5;

     setupMembers(m1, m2, m3, m4, m5);

     setupConnections(m1, m2, m3);

     demonstrateRecommendations(m1);

     demonstrateAdminOperations(m4);

     demonstratePasswordReset(m1);

     std::cout << "Simulation completed successfully.\n";

     return 0;
}

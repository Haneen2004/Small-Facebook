#ifndef ADMIN_HPP
#define ADMIN_HPP

#pragma once
#include <memory>
#include "Person.hpp"
#include "Page.hpp"
#include "Member.hpp"
#include "AccountStatus.hpp"

class Admin : public Person
{
public:
    Admin() = default;
    explicit Admin(const std::string &adminId)
    {
        setId(adminId);
    }

    // Business Logic: Block a user by changing their status to BLACKLISTED
    bool blockUser(int memberId)
    {
        auto member = Member::getMemberById(memberId);
        if (member)
        {
            member->setStatus(AccountStatus::BLACKLISTED);
            return true;
        }
        return false; // Member not found
    }

    // Business Logic: Unblock a user by setting status back to ACTIVE
    bool unblockUser(int memberId)
    {
        auto member = Member::getMemberById(memberId);
        if (member)
        {
            member->setStatus(AccountStatus::ACTIVE);
            return true;
        }
        return false; // Member not found
    }

    // Business Logic: Enable a social page
    bool enablePage(Page &page)
    {
        page.setActive(true);
        return true;
    }

    // Business Logic: Disable a social page
    bool disablePage(Page &page)
    {
        page.setActive(false);
        return true;
    }
};

#endif
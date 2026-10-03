#ifndef CONNECTION_INVITATION_HPP
#define CONNECTION_INVITATION_HPP

#pragma once
#include <memory>
#include <ctime>
#include "ConnectionInvitationStatus.hpp"

class Member;

class ConnectionInvitation
{
private:
    std::shared_ptr<Member> memberInvited;
    ConnectionInvitationStatus status{ConnectionInvitationStatus::PENDING};
    time_t dateCreated{time(nullptr)};
    time_t dateUpdated{time(nullptr)};

public:
    ConnectionInvitation(std::shared_ptr<Member> invited)
        : memberInvited(move(invited)) {}

    bool acceptConnection()
    {
        status = ConnectionInvitationStatus::ACCEPTED;
        dateUpdated = time(nullptr);
        return true;
    }

    bool rejectConnection()
    {
        status = ConnectionInvitationStatus::REJECTED;
        dateUpdated = time(nullptr);
        return true;
    }

    ConnectionInvitationStatus getStatus() const { return status; }
    std::shared_ptr<Member> getMemberInvited() const { return memberInvited; }
};

#endif

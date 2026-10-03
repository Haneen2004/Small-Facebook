#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#pragma once
#include <string>
#include "AccountStatus.hpp"

class Account
{
private:
    std::string id;
    std::string password;
    AccountStatus status{AccountStatus::ACTIVE};

public:
    virtual ~Account() = default;

    std::string getId() const { return id; }
    void setId(const std::string &newId) { id = newId; }

    std::string getPassword() const { return password; }
    void setPassword(const std::string &pwd) { password = pwd; }

    AccountStatus getStatus() const { return status; }
    void setStatus(AccountStatus newStatus) { status = newStatus; }

    virtual bool resetPassword(const std::string &newPassword)
    {
        if (newPassword.empty() || newPassword == this->password)
        {
            return false; // Validation failed
        }
        this->password = newPassword;
        return true;
    }
};

#endif

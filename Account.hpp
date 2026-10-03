#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#pragma once
#include <string>
#include "AccountStatus.hpp"

using namespace std;

class Account
{
private:
    string id;
    string password;
    AccountStatus status{AccountStatus::ACTIVE};

public:
    virtual ~Account() = default;

    string getId() const { return id; }
    void setId(const string &newId) { id = newId; }

    string getPassword() const { return password; }
    void setPassword(const string &pwd) { password = pwd; }

    AccountStatus getStatus() const { return status; }
    void setStatus(AccountStatus newStatus) { status = newStatus; }

    virtual bool resetPassword(const string &newPassword)
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
#ifndef PERSON_HPP
#define PERSON_HPP

#pragma once
#include <string>
#include <memory>
#include "Account.hpp"
#include "Address.hpp"

class Person : public Account
{
private:
    std::string name;
    Address address;
    std::string email;
    std::string phone;

public:
    virtual ~Person() = default;

    std::string getName() const { return name; }
    void setName(const std::string &newName) { name = newName; }

    Address getAddress() const { return address; }
    void setAddress(const Address &addr) { address = addr; }

    std::string getEmail() const { return email; }
    void setEmail(const std::string &newEmail) { email = newEmail; }

    std::string getPhone() const { return phone; }
    void setPhone(const std::string &newPhone) { phone = newPhone; }
};

#endif

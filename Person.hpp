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
    string name;
    Address address;
    string email;
    string phone;

public:
    virtual ~Person() = default;

    string getName() const { return name; }
    void setName(const string &newName) { name = newName; }

    Address getAddress() const { return address; }
    void setAddress(const Address &addr) { address = addr; }

    string getEmail() const { return email; }
    void setEmail(const string &newEmail) { email = newEmail; }

    string getPhone() const { return phone; }
    void setPhone(const string &newPhone) { phone = newPhone; }
};

#endif
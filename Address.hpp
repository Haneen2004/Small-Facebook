#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#pragma once
#include <string>
using namespace std;

class Address
{
private:
    string streetAddress;
    string city;
    string state;
    string zipCode;
    string country;

public:
    Address() = default;
    Address(string street, string cty, string st, string zip, string cntry)
        : streetAddress(move(street)), city(move(cty)), state(move(st)),
          zipCode(move(zip)), country(move(cntry)) {}

    string getStreetAddress() const { return streetAddress; }
    void setStreetAddress(const string &street) { streetAddress = street; }

    string getCity() const { return city; }
    void setCity(const string &cty) { city = cty; }

    string getState() const { return state; }
    void setState(const string &st) { state = st; }

    string getZipCode() const { return zipCode; }
    void setZipCode(const string &zip) { zipCode = zip; }

    string getCountry() const { return country; }
    void setCountry(const string &cntry) { country = cntry; }
};

#endif
#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#pragma once
#include <string>

class Address
{
private:
    std::string streetAddress;
    std::string city;
    std::string state;
    std::string zipCode;
    std::string country;

public:
    Address() = default;
    Address(std::string street, std::string cty, std::string st, std::string zip, std::string cntry)
        : streetAddress(move(street)), city(move(cty)), state(move(st)),
          zipCode(move(zip)), country(move(cntry)) {}

    std::string getStreetAddress() const { return streetAddress; }
    void setStreetAddress(const std::string &street) { streetAddress = street; }

    std::string getCity() const { return city; }
    void setCity(const std::string &cty) { city = cty; }

    std::string getState() const { return state; }
    void setState(const std::string &st) { state = st; }

    std::string getZipCode() const { return zipCode; }
    void setZipCode(const std::string &zip) { zipCode = zip; }

    std::string getCountry() const { return country; }
    void setCountry(const std::string &cntry) { country = cntry; }
};

#endif

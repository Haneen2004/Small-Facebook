#ifndef WORK_HPP
#define WORK_HPP

#pragma once
#include <string>
#include <ctime>
using namespace std;

class Work
{
private:
    string title;
    string company;
    string location;
    time_t fromDate{};
    time_t toDate{};
    string description;

public:
    Work() = default;

    string getTitle() const { return title; }
    void setTitle(const string &t) { title = t; }

    string getCompany() const { return company; }
    void setCompany(const string &c) { company = c; }

    string getLocation() const { return location; }
    void setLocation(const string &l) { location = l; }

    time_t getFromDate() const { return fromDate; }
    void setFromDate(time_t f) { fromDate = f; }

    time_t getToDate() const { return toDate; }
    void setToDate(time_t t) { toDate = t; }

    string getDescription() const { return description; }
    void setDescription(const string &d) { description = d; }
};

#endif
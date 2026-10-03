#ifndef WORK_HPP
#define WORK_HPP

#pragma once
#include <string>
#include <ctime>

class Work
{
private:
    std::string title;
    std::string company;
    std::string location;
    time_t fromDate{};
    time_t toDate{};
    std::string description;

public:
    Work() = default;

    std::string getTitle() const { return title; }
    void setTitle(const std::string &t) { title = t; }

    std::string getCompany() const { return company; }
    void setCompany(const std::string &c) { company = c; }

    std::string getLocation() const { return location; }
    void setLocation(const std::string &l) { location = l; }

    time_t getFromDate() const { return fromDate; }
    void setFromDate(time_t f) { fromDate = f; }

    time_t getToDate() const { return toDate; }
    void setToDate(time_t t) { toDate = t; }

    std::string getDescription() const { return description; }
    void setDescription(const std::string &d) { description = d; }
};

#endif

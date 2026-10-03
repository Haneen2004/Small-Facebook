#ifndef PAGE_HPP
#define PAGE_HPP

#pragma once
#include <string>
#include <vector>
#include "Recommendation.hpp"

class Page
{
private:
    int pageId{0};
    string name;
    string description;
    string type;
    int totalMembers{0};
    vector<Recommendation> recommendations;
    bool active{true};

public:
    Page() = default;
    Page(int id, string n) : pageId(id), name(move(n)) {}

    int getPageId() const { return pageId; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    int getTotalMembers() const { return totalMembers; }

    bool isActive() const { return active; }
    void setActive(bool status) { active = status; }

    void addRecommendation(const Recommendation &rec)
    {
        recommendations.push_back(rec);
    }

    vector<Recommendation> getRecommendations() const
    {
        return recommendations;
    }
};

#endif
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
    std::string name;
    std::string description;
    std::string type;
    int totalMembers{0};
    std::vector<Recommendation> recommendations;
    bool active{true};

public:
    Page() = default;
    Page(int id, std::string n) : pageId(id), name(std::move(n)) {}

    int getPageId() const { return pageId; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    int getTotalMembers() const { return totalMembers; }

    bool isActive() const { return active; }
    void setActive(bool status) { active = status; }

    void addRecommendation(const Recommendation &rec)
    {
        recommendations.push_back(rec);
    }

    std::vector<Recommendation> getRecommendations() const
    {
        return recommendations;
    }
};

#endif

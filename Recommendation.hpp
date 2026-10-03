#ifndef RECOMMENDATION_HPP
#define RECOMMENDATION_HPP

#pragma once
#include <string>
#include <vector>
#include <ctime>

class Recommendation
{
private:
    int recommendationId{0};
    int rating{0};
    std::string description;
    time_t createdAt{time(nullptr)};
    std::vector<std::string> activeJobPostings;

public:
    Recommendation() = default;

    int getRecommendationId() const { return recommendationId; }
    int getRating() const { return rating; }
    std::string getDescription() const { return description; }
    time_t getCreatedAt() const { return createdAt; }
    std::vector<std::string> getActiveJobPostings() const { return activeJobPostings; }
};

#endif

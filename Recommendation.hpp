#ifndef RECOMMENDATION_HPP
#define RECOMMENDATION_HPP

#pragma once
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Recommendation
{
private:
    int recommendationId{0};
    int rating{0};
    string description;
    time_t createdAt{time(nullptr)};
    vector<string> activeJobPostings;

public:
    Recommendation() = default;

    int getRecommendationId() const { return recommendationId; }
    int getRating() const { return rating; }
    string getDescription() const { return description; }
    time_t getCreatedAt() const { return createdAt; }
    vector<string> getActiveJobPostings() const { return activeJobPostings; }
};

#endif
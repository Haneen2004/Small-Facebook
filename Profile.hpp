#ifndef PROFILE_HPP
#define PROFILE_HPP

#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "Work.hpp"

class Profile
{
private:
    vector<uint8_t> profilePicture;
    vector<uint8_t> coverPhoto;
    string gender;
    vector<Work> workExperiences;
    vector<string> educations;
    vector<string> places;
    vector<string> stats;

public:
    Profile() = default;

    bool addWorkExperience(const Work &work)
    {
        workExperiences.push_back(work);
        return true;
    }

    bool addEducation(const string &education)
    {
        educations.push_back(education);
        return true;
    }

    bool addPlace(const string &place)
    {
        places.push_back(place);
        return true;
    }

    vector<Work> getWorkExperiences() const { return workExperiences; }
    vector<string> getEducations() const { return educations; }
    vector<string> getPlaces() const { return places; }
};

#endif
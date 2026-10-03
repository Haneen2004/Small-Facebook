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
    std::vector<uint8_t> profilePicture;
    std::vector<uint8_t> coverPhoto;
    std::string gender;
    std::vector<Work> workExperiences;
    std::vector<std::string> educations;
    std::vector<std::string> places;
    std::vector<std::string> stats;

public:
    Profile() = default;

    bool addWorkExperience(const Work &work)
    {
        workExperiences.push_back(work);
        return true;
    }

    bool addEducation(const std::string &education)
    {
        educations.push_back(education);
        return true;
    }

    bool addPlace(const std::string &place)
    {
        places.push_back(place);
        return true;
    }

    std::vector<Work> getWorkExperiences() const { return workExperiences; }
    std::vector<std::string> getEducations() const { return educations; }
    std::vector<std::string> getPlaces() const { return places; }
};

#endif

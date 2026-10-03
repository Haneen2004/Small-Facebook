#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>

class Member;

class Message
{
private:
    int messageId{0};
    std::vector<std::shared_ptr<Member>> sentTo;
    std::string messageBody;
    std::vector<uint8_t> media;

public:
    Message() = default;

    bool addMember(const std::shared_ptr<Member> &member)
    {
        sentTo.push_back(member);
        return true;
    }

    std::string getMessageBody() const { return messageBody; }
    void setMessageBody(const std::string &body) { messageBody = body; }
};

#endif

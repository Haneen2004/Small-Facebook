#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
using namespace std;

class Member;

class Message
{
private:
    int messageId{0};
    vector<shared_ptr<Member>> sentTo;
    string messageBody;
    vector<uint8_t> media;

public:
    Message() = default;

    bool addMember(const shared_ptr<Member> &member)
    {
        sentTo.push_back(member);
        return true;
    }

    string getMessageBody() const { return messageBody; }
    void setMessageBody(const string &body) { messageBody = body; }
};

#endif
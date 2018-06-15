#pragma once
#include <exception>

class Exception : public std::exception
{
    std::string message;
public:
    Exception(const std::string& msg): message{ msg } {}
    Exception() {}

    virtual const char* what()
    {
        return this->message.c_str();
    }
};

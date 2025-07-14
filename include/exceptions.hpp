#pragma once
#include <exception>
#include <string>

class BaseException : public std::exception {
public:
    explicit BaseException(const std::string& message)
        : _msg(message) {}

    const char* what() const noexcept override {
        return _msg.c_str();
    }

protected:
    std::string _msg;
};

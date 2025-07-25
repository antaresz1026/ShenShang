#pragma once
#include <exception>
#include <string>

namespace shenshang::utils::exception {
    class BaseException : public std::exception {
    public:
        explicit BaseException(const std::string& message)
            : _msg(message) {}

        const char* what() const noexcept override;
    protected:
        std::string _msg;
    };

    class ConfigLoaderException : public BaseException {
    public:
        explicit ConfigLoaderException(const std::string& message)
            : BaseException("ConfigLoaderException: " + message) {}
    };

    class LoggerConfigException : public BaseException {
    public:
        explicit LoggerConfigException(const std::string& message)
            : BaseException("LoggerConfigException: " + message) {}
    };

    class BadRequestException : public BaseException {
    public:
        explicit BadRequestException(const std::string& message)
            : BaseException("BadRequestException: " + message) {}
    };

    class InternalErrorException : public BaseException {
    public:
        explicit InternalErrorException(const std::string& message)
            : BaseException("InternalErrorException: " + message) {}
    };
}

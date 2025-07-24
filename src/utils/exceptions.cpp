#include "utils/exceptions.hpp"

const char* shenshang::exception::BaseException::what() const noexcept {
    return _msg.c_str();
}
#include "utils/exceptions.hpp"

const char* shenshang::utils::exception::BaseException::what() const noexcept {
    return _msg.c_str();
}
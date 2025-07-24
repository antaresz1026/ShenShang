#include "utils/password.hpp"
#include <sodium.h>
#include <stdexcept>

namespace shenshang::utils::password {

void init() {
    if (sodium_init() < 0) {
        throw std::runtime_error("libsodium 初始化失败");
    }
}

std::string hash(const std::string& password) {
    char out[crypto_pwhash_STRBYTES];
    if (crypto_pwhash_str(
            out,
            password.c_str(),
            password.size(),
            crypto_pwhash_OPSLIMIT_INTERACTIVE,
            crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
        throw std::runtime_error("密码哈希失败: 资源不足");
    }
    return std::string(out);
}

bool verify(const std::string& password, const std::string& hashed) {
    return crypto_pwhash_str_verify(
        hashed.c_str(),
        password.c_str(),
        password.size()
    ) == 0;
}

} // namespace utils::password

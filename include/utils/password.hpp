#include <string>

namespace shenshang::utils::password {
    void init();
    std::string hash(const std::string& password);
    bool verify(const std::string& password, const std::string& hashed);
}
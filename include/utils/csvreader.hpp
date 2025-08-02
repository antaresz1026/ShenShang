#include <string>
#include <vector>
#include <application_layer/question.hpp>

namespace shenshang::utils::csv {
    std::vector<std::string> split(const std::string& s, char delim);
    std::vector<shenshang::question::Question> parseCSV(const std::string& filepath);
}
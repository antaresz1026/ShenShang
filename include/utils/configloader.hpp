#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>

namespace shenshang::config_loader {
    class ConfigLoader {
    public:
        explicit ConfigLoader(const std::string& file) {
            boost::property_tree::ini_parser::read_ini(file, pt_);
        }
        template <typename T>
        T get(const std::string& key) const {
            return pt_.get<T>(key);
        }
    private:
        boost::property_tree::ptree pt_;
    };
}

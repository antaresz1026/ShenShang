#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>

class ConfigLoader {
public:
    explicit ConfigLoader(const std::string& file) {
        boost::property_tree::ini_parser::read_ini(file, pt_);
    }

    std::string getHost() const {
        return pt_.get<std::string>("server.host");
    }

    int getPort() const {
        return pt_.get<int>("server.port");
    }

    std::string getUser() const {
        return pt_.get<std::string>("database.user");
    }

    std::string getPassword() const {
        return pt_.get<std::string>("database.password");
    }

private:
    boost::property_tree::ptree pt_;
};

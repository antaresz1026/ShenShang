#include <gtest/gtest.h>
#include "configloader.hpp"
#include "exceptions.hpp"
#include <iostream>

class ConfigLoaderException : public BaseException {
public:
    explicit ConfigLoaderException(const std::string& message)
        : BaseException("ConfigLoaderException: " + message) {}
};

TEST(ConfigLoaderTest, BasicRead) {
    try {
        ConfigLoader loader("/home/antaresz/Projects/ShenShang/settings/default.ini");
        EXPECT_EQ(loader.get<std::string>("server.host"), "192.168.64.134");
        EXPECT_EQ(loader.get<uint16_t>("server.port"), 8080);
        EXPECT_EQ(loader.get<std::string>("database.user"), "antaresz");
        EXPECT_EQ(loader.get<std::string>("database.password"), "170319");
    } catch(const ConfigLoaderException& e) {
        std::cout << e.what() << "\n";
    }

}

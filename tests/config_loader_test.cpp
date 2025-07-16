#include <gtest/gtest.h>
#include "basic_layer/configloader.hpp"
#include "basic_layer/exceptions.hpp"
#include <iostream>

TEST(ConfigLoaderTest, BasicRead) {
    try {
        shenshang::config_loader::ConfigLoader loader("/home/antaresz/Projects/ShenShang/settings/default.ini");
        EXPECT_EQ(loader.get<std::string>("server.host"), "192.168.64.134");
        EXPECT_EQ(loader.get<uint16_t>("server.port"), 8080);
        EXPECT_EQ(loader.get<std::string>("database.user"), "antaresz");
        EXPECT_EQ(loader.get<std::string>("database.password"), "170319");
    } catch(const shenshang::exception::ConfigLoaderException& e) {
        std::cout << e.what() << "\n";
    }

}

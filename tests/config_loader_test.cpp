#include <gtest/gtest.h>
#include "configloader.hpp"

TEST(ConfigLoaderTest, BasicRead) {
    ConfigLoader loader("/home/antaresz/Projects/ShenShang/settings/default.ini");
    EXPECT_EQ(loader.getHost(), "192.168.64.134");
    EXPECT_EQ(loader.getPort(), 8080);
    EXPECT_EQ(loader.getUser(), "antaresz");
    EXPECT_EQ(loader.getPassword(), "170319");
}

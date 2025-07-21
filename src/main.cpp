#include <iostream>
#include <string>
#include "basic_layer/logger.hpp"

int main(int argc, char** argv) {
    shenshang::logger::Logger::init();
    shenshang::logger::Logger::info("test1");
    shenshang::logger::Logger::init();
    shenshang::logger::Logger::info("test2");
    return 0;
}
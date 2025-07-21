#include <iostream>
#include <string>
#include "basic_layer/logger.hpp"
#include "basic_layer/configloader.hpp"
#include "logic_layer/apicontroller.hpp"

int main(int argc, char** argv) {
    shenshang::logger::Logger::init();
    shenshang::config_loader::ConfigLoader cf("/home/antaresz/Projects/ShenShang/settings/default.ini");
    APIController apic;
    drogon::app().addListener(cf.get<std::string>("server.host"), cf.get<std::uint16_t>("server.port"));
    drogon::app().run();
    return 0;
}
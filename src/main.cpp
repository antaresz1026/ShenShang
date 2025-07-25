#include <iostream>
#include <string>
#include "utils/logger.hpp"
#include "utils/configloader.hpp"
#include "logic_layer/apicontroller.hpp"
#include "basic_layer/sqlconnection.hpp"

int main(int argc, char** argv) {
    shenshang::utils::logger::Logger::init();
    shenshang::utils::config_loader::ConfigLoader cf("/home/antaresz/Projects/ShenShang/settings/default.ini");
    shenshang::db::SQLConnection::init(cf.get<std::string>("database.connectionstring"));
    APIController apic;
    drogon::app().addListener(cf.get<std::string>("server.host"), cf.get<std::uint16_t>("server.port"));
    drogon::app().run();
    return 0;
}
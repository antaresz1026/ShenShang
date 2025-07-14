#include "apicontroller.hpp"
#include "configloader.hpp"
#include <drogon/drogon.h>

int main(int argc, char** argv) {
    ConfigLoader cf("/home/antaresz/Projects/ShenShang/settings/default.ini");
    APIController apic;
    drogon::app().addListener(cf.get<std::string>("server.host"), cf.get<uint16_t>("server.port")).run();
    return 0;
}
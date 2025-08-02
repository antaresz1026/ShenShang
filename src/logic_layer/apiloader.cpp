#include <drogon/drogon.h>
#include "logic_layer/apicontroller.hpp"

using namespace drogon;

void shenshang::api::registerAllAPIs() {
    AUTO_REGISTER_API(shenshang::api::UserLogin, user_login, "/api/login",  METHODS(drogon::Post));
    AUTO_REGISTER_API(shenshang::api::UserRegister, user_register, "/api/register",  METHODS(drogon::Post));
    AUTO_REGISTER_API(shenshang::api::FileUpload, file_upload, "/api/fileupload",  METHODS(drogon::Post, drogon::Options));
}
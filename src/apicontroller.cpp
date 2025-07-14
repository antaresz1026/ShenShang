#include "apicontroller.hpp"
#include <drogon/drogon.h>
#include <json/json.h>

void APIController::rep(const std::string& msg,
                                   std::function<void(const drogon::HttpResponsePtr &)> &&callback)
{
    Json::Value result;
    result["msg"] = msg;
    auto resp = drogon::HttpResponse::newHttpJsonResponse(result);
    callback(std::move(resp));
}

void APIController::hello(const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
    this->rep("hello drogon", std::move(callback));
}
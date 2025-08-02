#pragma once
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <functional>

namespace shenshang::api {

class APIBase {
    public:
        virtual ~APIBase() = default;
        virtual void handle(const drogon::HttpRequestPtr &req,
                            std::function<void(const drogon::HttpResponsePtr &)> &&callback) = 0;
    protected:
        static void rep(bool success, const std::string& msg, const Json::Value& extra,
                        std::function<void(const drogon::HttpResponsePtr&)> callback) {
            Json::Value resp;
            resp["success"] = success;
            resp["msg"] = msg;
            for (const auto& key : extra.getMemberNames()) {
                resp[key] = extra[key];
            }
            callback(drogon::HttpResponse::newHttpJsonResponse(resp));
        }

        static void rep(bool success, const std::string& msg,
                        std::function<void(const drogon::HttpResponsePtr&)> callback) {
            rep(success, msg, Json::Value(), std::move(callback));
        }

        static void rep(const std::string& msg,
                        std::function<void(const drogon::HttpResponsePtr&)> callback) {
            rep(false, msg, Json::Value(), std::move(callback));
        }
};

}
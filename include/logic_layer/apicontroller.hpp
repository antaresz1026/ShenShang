#pragma once
#include "apibase.hpp"
#include <drogon/drogon.h>

#define AUTO_REGISTER_API(CLASS_NAME, HANDLER_VAR, PATH, CONSTRAINTS)                     \
    static CLASS_NAME* HANDLER_VAR = new CLASS_NAME();                                    \
    drogon::app().registerHandler(                                                        \
        PATH,                                                                              \
        [](const drogon::HttpRequestPtr& req,                                              \
           std::function<void(const drogon::HttpResponsePtr&)>&& cb) {                    \
            HANDLER_VAR->handle(req, std::move(cb));                                       \
        },                                                                                 \
        CONSTRAINTS)

#define METHODS(...) std::vector<drogon::internal::HttpConstraint>{__VA_ARGS__}




namespace shenshang::api {
    class UserLogin : public shenshang::api::APIBase {
        public:
            void handle(const drogon::HttpRequestPtr &req,
                        std::function<void(const drogon::HttpResponsePtr &)> &&callback) override;
    };
    class UserRegister : public shenshang::api::APIBase {
        public:
            void handle(const drogon::HttpRequestPtr &req,
                        std::function<void(const drogon::HttpResponsePtr &)> &&callback) override;
    };
    class QuestionsUpload : public shenshang::api::APIBase {
        public:
            void handle(const drogon::HttpRequestPtr &req,
                        std::function<void(const drogon::HttpResponsePtr &)> &&callback) override;
    };
    void registerAllAPIs();
}
#include "logic_layer/apicontroller.hpp"
#include "utils/password.hpp"
#include <drogon/drogon.h>
#include <json/json.h>

void APIController::hello(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
    this->rep("hello drogon", std::move(callback));
}

void APIController::user_login(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto json = req->getJsonObject();
    if (!json || !json->isMember("name") || !json->isMember("password")) {
        return rep("缺少用户名或密码", std::move(callback));
    }

    std::string name = (*json)["name"].asString();
    std::string password = (*json)["password"].asString();

    auto client = drogon::app().getDbClient();
    client->execSqlAsync("SELECT user_id, user_password, user_avatar FROM shenshang.users WHERE name = $1",
        [=, callback = std::move(callback)](const drogon::orm::Result &r) {
            if (r.empty()) {
                return this->rep("用户不存在", std::move(callback));
            }

            auto row = r[0];
            std::string dbHash = row["password"].as<std::string>();
            if (!shenshang::utils::password::verify(password, dbHash)) {
                return this->rep("密码错误", std::move(callback));
            }

            std::string token = drogon::utils::getUuid();

            Json::Value extra;
            extra["token"] = token;
            extra["user"]["id"] = row["id"].as<int>();
            extra["user"]["name"] = name;
            extra["user"]["avatar"] = row["avatar"].as<std::string>();

            this->rep(true, "登录成功", extra, std::move(callback));
        },
        [=, callback = std::move(callback)](const drogon::orm::DrogonDbException &e) {
            this->rep(std::string("数据库错误: ") + e.base().what(), std::move(callback));
        },
        name);
}

void APIController::user_register(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto json = req->getJsonObject();
    if (!json || !json->isMember("name") || !json->isMember("password")) {
        return rep("输入格式错误", std::move(callback));
    }

    std::string name = (*json)["name"].asString();
    std::string password = (*json)["password"].asString();
    std::string avatar = (*json)["avatar"].asString();

    auto client = drogon::app().getDbClient();
    client->execSqlAsync("SELECT user_id FROM shenshang.users WHERE user_name = $1",
        [=, callback = std::move(callback)](const drogon::orm::Result &r) {
            if (!r.empty()) {
                return this->rep("用户已存在", std::move(callback));
            }

            std::string hashed = shenshang::utils::password::hash(password);

            client->execSqlAsync("INSERT INTO shenshang.users(user_name, user_avatar, user_password) VALUES ($1, $2, $3)",
                [=](const drogon::orm::Result &) {
                    this->rep(true, "注册成功", std::move(callback));
                },
                [=](const drogon::orm::DrogonDbException &e) {
                    this->rep(std::string("插入失败: ") + e.base().what(), std::move(callback));
                },
                name, avatar, hashed);
        },
        [=, callback = std::move(callback)](const drogon::orm::DrogonDbException &e) {
            this->rep(std::string("查询失败: ") + e.base().what(), std::move(callback));
        },
        name);
}

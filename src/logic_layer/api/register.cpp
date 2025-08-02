#include "logic_layer/apicontroller.hpp"
#include "utils/password.hpp"
#include "utils/logger.hpp"
#include "utils/exceptions.hpp"
#include "basic_layer/sqlconnection.hpp"
#include <drogon/drogon.h>
#include <json/json.h>
#include <string>

using shenshang::utils::logger::Logger;
using shenshang::utils::exception::BadRequestException;
using shenshang::utils::exception::InternalErrorException;

void shenshang::api::UserRegister::handle(const drogon::HttpRequestPtr &req,
                                  std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto safe_callback = std::make_shared<std::function<void(const drogon::HttpResponsePtr&)>>(std::move(callback));
    try {
        auto json = req->getJsonObject();
        if (!json) {
            Logger::error("请求体不是 JSON");
            throw BadRequestException("请求体不是合法 JSON");
        }
        if (!json->isMember("name") || !json->isMember("password") || !json->isMember("avatar")) {
            Logger::warn("Register failed: missing fields");
            throw BadRequestException("输入格式错误");
        }

        std::string name = (*json)["name"].asString();
        std::string password = (*json)["password"].asString();
        std::string avatar = (*json)["avatar"].asString();

        auto client = shenshang::db::SQLConnection::client();
        if (!client) {
            Logger::fatal("getDbClient() 返回 nullptr，数据库连接未初始化！");
            throw shenshang::utils::exception::InternalErrorException("数据库连接异常");
        }
        client->execSqlAsync(
            "SELECT user_id FROM shenshang.users WHERE user_name = $1",
            [=](const drogon::orm::Result &r) {
                if (!r.empty()) {
                    Logger::warn("Register failed: user '{}' already exists", name);
                    return this->rep("用户已存在", *safe_callback);
                }

                std::string hashed = shenshang::utils::password::hash(password);

                client->execSqlAsync(
                    "INSERT INTO shenshang.users(user_name, user_avatar, user_password) VALUES ($1, $2, $3)",
                    [=](const drogon::orm::Result &) {
                        Logger::info("User '{}' registered successfully", name);
                        this->rep(true, "注册成功", *safe_callback);
                    },
                    [=](const drogon::orm::DrogonDbException &e) {
                        Logger::error("Register insert error: {}", e.base().what());
                        this->rep(std::string("插入失败: ") + e.base().what(), *safe_callback);
                    },
                    name, avatar, hashed);
            },
            [=](const drogon::orm::DrogonDbException &e) {
                Logger::error("Register query error: {}", e.base().what());
                this->rep(std::string("查询失败: ") + e.base().what(), *safe_callback);
            },
            name);

    } catch (const BadRequestException& e) {
        this->rep(e.what(), *safe_callback);
    } catch (const std::exception& e) {
        Logger::error("Register exception: {}", e.what());
        this->rep("服务器内部错误", *safe_callback);
    }
}
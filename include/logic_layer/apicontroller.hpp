#include <drogon/drogon.h>

class APIController : public drogon::HttpController<APIController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(APIController::hello, "/api/hello", drogon::Get);
    ADD_METHOD_TO(APIController::user_login, "/api/login", drogon::Post);
    ADD_METHOD_TO(APIController::user_register, "/api/register", drogon::Post);
    METHOD_LIST_END

    void hello(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback);
    void user_login(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback);
    void user_register(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback);

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

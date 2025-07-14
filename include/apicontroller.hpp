#include <drogon/HttpController.h>
#include <nlohmann/json.hpp>

class APIController : public drogon::HttpController<APIController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(APIController::hello, "/api/hello", drogon::Get);
    METHOD_LIST_END

    void rep(std::string code, std::string msg, nl)

    void hello(const drogon::HttpRequestPtr& req,
               std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};

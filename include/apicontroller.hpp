#include <drogon/drogon.h>

class APIController : public drogon::HttpController<APIController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(APIController::hello, "/api/hello", drogon::Get);
    METHOD_LIST_END

    void rep(const std::string& msg,
                                   std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void hello(const drogon::HttpRequestPtr& req,
               std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};

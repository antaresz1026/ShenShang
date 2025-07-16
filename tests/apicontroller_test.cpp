#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <drogon/drogon.h>
#include "logic_layer/apicontroller.hpp"
#include <json/json.h>

TEST(APIControllerTest, HelloResponseContainsMsg)
{
    APIController ctrl;

    std::promise<std::string_view> promise;
    auto future = promise.get_future();

    // 传入一个空请求（mock）
    drogon::HttpRequestPtr req = drogon::HttpRequest::newHttpRequest();

    // 传入测试回调，拦截 controller 的返回响应
    ctrl.hello(req, [&promise](const drogon::HttpResponsePtr &resp) {
        std::string_view body = resp->getBody();
        promise.set_value(body);
    });

    ASSERT_EQ(future.wait_for(std::chrono::seconds(1)), std::future_status::ready);

    std::string_view _result = future.get();
    std::string result(_result);
    // 解析JSON响应
    Json::Reader reader;
    Json::Value root;
    ASSERT_TRUE(reader.parse(result, root));
    
    // 检查JSON中的msg字段
    EXPECT_EQ(root["msg"].asString(), "hello drogon");
}
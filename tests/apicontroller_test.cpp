#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <drogon/drogon.h>
#include "logic_layer/apicontroller.hpp"
#include <json/json.h>
#include <iostream>

TEST(APIControllerTest, HelloResponseContainsMsg)
{
    // Step 1: 创建 HttpClient，指向你的本地服务（端口和协议请与实际一致）
    auto client = drogon::HttpClient::newHttpClient("http://192.168.64.134:8080");  // 8080端口需与你服务端口一致

    // Step 2: 构造 HTTP 请求，设置路径
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setPath("/api/hello");         // 替换为你的API路由
    req->setMethod(drogon::Get);    // 或 drogon::Post 等
    req->addHeader("Accept-Encoding", "identity"); // 禁止压缩，确保响应体为明文JSON

    // Step 3: 发送请求并同步等待结果（promise）
    std::promise<std::string_view> promise;
    auto future = promise.get_future();

    client->sendRequest(req, [&promise](drogon::ReqResult result, const drogon::HttpResponsePtr& resp) {
        if(result == drogon::ReqResult::Ok && resp) {
            std::string_view body = resp->getBody();
            std::cout << "收到响应体: " << body << std::endl;
            promise.set_value(body);
        } else {
            std::cerr << "请求失败: " << (int)result << std::endl;
            promise.set_value(""); // 失败时给个空串
        }
    });

    // Step 4: 等待响应
    ASSERT_EQ(future.wait_for(std::chrono::seconds(2)), std::future_status::ready);
    std::string_view result = future.get();
    std::string jsonStr(result);
    Json::Value root;
    Json::Reader reader;
    ASSERT_TRUE(reader.parse(jsonStr, root));
    EXPECT_EQ(root["msg"].asString(), "hello drogon");
}
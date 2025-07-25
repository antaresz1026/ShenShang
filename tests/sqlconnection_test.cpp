#include <gtest/gtest.h>
#include "basic_layer/sqlconnection.hpp"
#include <drogon/orm/DbClient.h>
#include <drogon/drogon.h>

using namespace shenshang::db;

TEST(SQLConnectionTest, InitAndGetClient) {
    // 模拟一个合法 URI（替换为你本地可用的 PostgreSQL 数据库）
    const std::string dbURI = "host=127.0.0.1 port=5432 dbname=shenshang user=shenshang_connector password=170319 sslmode=disable";

    // 初始化连接
    SQLConnection::init(dbURI);

    // 获取连接客户端
    auto client = SQLConnection::client();

    // 断言 client 非空
    ASSERT_TRUE(client != nullptr);

    // 运行一个简单查询
    std::promise<bool> success;
    auto future = success.get_future();

    client->execSqlAsync("SELECT 1",
        [&success](const drogon::orm::Result &result) {
            success.set_value(true);
        },
        [&success](const drogon::orm::DrogonDbException &err) {
            std::cerr << "Database error: " << err.base().what() << std::endl;
            success.set_value(false);
        });

    // 等待异步结果
    ASSERT_TRUE(future.wait_for(std::chrono::seconds(3)) == std::future_status::ready);
    EXPECT_TRUE(future.get());
}


#include <mutex>
#include <condition_variable>
#include "logic_layer/sqlconnection.hpp"
#include <gtest/gtest.h>

TEST_F(SQLConnectionInitTest, ClientInitializationTest) {
    auto client = shenshang::db::SQLConnection::client();
    ASSERT_NE(client, nullptr) << "DbClientPtr should not be null";
}

TEST_F(SQLConnectionTest, BasicQueryTest) {
    auto client = shenshang::db::SQLConnection::client();
    ASSERT_NE(client, nullptr);

    std::condition_variable cv;
    std::mutex mtx;
    bool finished = false;
    bool success = false;

    client->execSqlAsync("SELECT 1",
        [&](const drogon::orm::Result &result) {
            EXPECT_EQ(result.size(), 1);
            EXPECT_EQ(result[0][0].as<int>(), 1);
            success = true;
            std::lock_guard<std::mutex> lock(mtx);
            finished = true;
            cv.notify_one();
        },
        [&](const drogon::orm::DrogonDbException &e) {
            ADD_FAILURE() << "SQL error: " << e.base().what();
            std::lock_guard<std::mutex> lock(mtx);
            finished = true;
            cv.notify_one();
        });

    // 等待异步执行完成
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait_for(lock, std::chrono::seconds(3), [&] { return finished; });

    ASSERT_TRUE(success);
}
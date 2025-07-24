#include <gtest/gtest.h>
#include <mutex>
#include <condition_variable>
#include "basic_layer/sqlconnection.hpp"

class SQLConnectionTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // 初始化数据库连接
        shenshang::db::SQLConnection::init(
            "host=127.0.0.1 port=5432 dbname=shenshang user=shenshang_connector password=170319 sslmode=disable"
        );
    }
};

TEST_F(SQLConnectionTest, InitOnce) {
    auto client = shenshang::db::SQLConnection::client();
    ASSERT_NE(client, nullptr);
}

TEST_F(SQLConnectionTest, SelectOneTest) {
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

    std::unique_lock<std::mutex> lock(mtx);
    cv.wait_for(lock, std::chrono::seconds(5), [&] { return finished; });

    ASSERT_TRUE(success);
}

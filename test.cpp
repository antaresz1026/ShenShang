#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
#include <iostream>

int main() {
    auto client = drogon::orm::DbClient::newPgClient(
        "host=127.0.0.1 port=5432 dbname=shenshang user=shenshang_connector password=170319 sslmode=disable",
        1  // connection pool size
    );

    client->execSqlAsync(
        "SELECT 1",
        [](const drogon::orm::Result &res) {
            std::cout << "Connection test OK. Got " << res[0][0].as<int>() << std::endl;
        },
        [](const drogon::orm::DrogonDbException &e) {
            std::cerr << "Error: " << e.base().what() << std::endl;
        });

    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}

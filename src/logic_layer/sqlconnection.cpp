#include "logic_layer/sqlconnection.hpp"
#include <mutex>

namespace shenshang::db {
    void SQLConnection::init(const std::string& dbURI) {
            static std::once_flag flag;
            std::call_once(flag, [dbURI]() {
                _dbClient = drogon::orm::DbClient::newPgClient(dbURI, 16);
            });
    }
    drogon::orm::DbClientPtr SQLConnection::client() {
        return _dbClient;
    }
}

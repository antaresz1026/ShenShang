#include "logic_layer/sqlconnection.hpp"
#include <mutex>

namespace shenshang::db {
    void SqlConnection::init(const std::string& dbURI) {
            static std::once_flag flag;
            std::call_once(flag, [dbURI]() {
                _dbClient = drogon::orm::DbClient::newMysqlClient(dbURI, 16);
            });
    }
    drogon::orm::DbClientPtr SqlConnection::client() {
        return _dbClient;
    }
}

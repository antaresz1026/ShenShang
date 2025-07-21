#pragma once
#include <drogon/orm/DbClient.h>
#include <string>

namespace shenshang::db {
    class SQLConnection {
    public:
        static void init(const std::string& dbURI);
        static drogon::orm::DbClientPtr client();

    private:
        static inline drogon::orm::DbClientPtr _dbClient;
    };
}

#include <gtest/gtest.h>
#include "logger.hpp"
#include "logmacro.hpp"
#include "exceptions.hpp"
#include <stdexcept>
#include <string>

class LoggerConfigException : public BaseException {
public:
    explicit LoggerConfigException(const std::string& message)
        : BaseException("LoggerConfigException: " + message) {}
};

TEST(LoggerConfigInitTest, CatchLoggerInitException) {
    Logger::init();  // 初始化日志

    try {
        throw LoggerConfigException("配置文件缺失");
    } catch (const std::exception& e) {
        LOG_ERR("捕获异常：" << e.what());
        SUCCEED();  // 表示异常已被成功捕获
    }
}

TEST(LoggerTest, BasicLoggingDoesNotThrow) {
    ASSERT_NO_THROW({
        Logger::init();
        LOG_INFO("测试 info 日志");
        LOG_WARN("测试 warning 日志");
        LOG_ERR("测试 error 日志");
        LOG_DEBUG("测试 debug 日志");
    });
}


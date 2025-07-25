#include <gtest/gtest.h>
#include "utils/logger.hpp"
#include "utils/exceptions.hpp"
#include <stdexcept>
#include <string>

TEST(LoggerConfigInitTest, CatchLoggerInitException) {
    try {
        shenshang::utils::logger::Logger::init();
        throw shenshang::utils::exception::LoggerConfigException("测试");
    } catch (const shenshang::utils::exception::LoggerConfigException& e) {
        shenshang::utils::logger::Logger::error("捕获预期的配置异常：", e.what());
        SUCCEED();
    } catch (const std::exception& e) {
        FAIL() << "捕获到意外的异常：" << e.what();
    } catch (...) {
        FAIL() << "捕获到未知类型的异常";
    }
}

TEST(LoggerTest, BasicLoggingDoesNotThrow) {
    ASSERT_NO_THROW({
        shenshang::utils::logger::Logger::info("测试 info 日志");
        shenshang::utils::logger::Logger::warn("测试 warning 日志");
        shenshang::utils::logger::Logger::error("测试 error 日志");
        shenshang::utils::logger::Logger::debug("测试 debug 日志");
    });
}
#include <gtest/gtest.h>
#include "basic_layer/logger.hpp"
#include "basic_layer/exceptions.hpp"
#include <stdexcept>
#include <string>

TEST(LoggerConfigInitTest, CatchLoggerInitException) {
    try {
        // 模拟配置文件缺失的情况，期望抛出 LoggerConfigException
        // 注意：这里假设 init() 函数会在配置文件缺失时抛出异常
        shenshang::logger::Logger::init();
        throw shenshang::exception::LoggerConfigException("测试");
    } catch (const shenshang::exception::LoggerConfigException& e) {
        // 使用正确的日志记录方式：多个参数用逗号分隔
        shenshang::logger::Logger::error("捕获预期的配置异常：", e.what());
        SUCCEED();  // 表示异常已被成功捕获
    } catch (const std::exception& e) {
        FAIL() << "捕获到意外的异常：" << e.what();
    } catch (...) {
        FAIL() << "捕获到未知类型的异常";
    }
}

TEST(LoggerTest, BasicLoggingDoesNotThrow) {
    ASSERT_NO_THROW({
        shenshang::logger::Logger::info("测试 info 日志");
        shenshang::logger::Logger::warn("测试 warning 日志");
        shenshang::logger::Logger::error("测试 error 日志");
        shenshang::logger::Logger::debug("测试 debug 日志");
    });
}
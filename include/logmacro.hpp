#pragma once
#include "logger.hpp"
#include <sstream>

// 内部宏：用于处理流拼接
#define _LOG_WITH_LEVEL(level, msg)                            \
    do {                                                       \
        std::ostringstream oss__;                              \
        oss__ << msg;                                          \
        BOOST_LOG_SEV(Logger::get(), boost::log::trivial::level) << oss__.str(); \
    } while (0)

// 对外暴露的宏
#define LOG_TRACE(msg) _LOG_WITH_LEVEL(trace, msg)
#define LOG_DEBUG(msg) _LOG_WITH_LEVEL(debug, msg)
#define LOG_INFO(msg)  _LOG_WITH_LEVEL(info, msg)
#define LOG_WARN(msg)  _LOG_WITH_LEVEL(warning, msg)
#define LOG_ERR(msg)   _LOG_WITH_LEVEL(error, msg)
#define LOG_FATAL(msg) _LOG_WITH_LEVEL(fatal, msg)

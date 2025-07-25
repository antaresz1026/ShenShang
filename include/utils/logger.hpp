#pragma once
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>

#include <sstream>
#include <string_view>

namespace shenshang::utils::logger {

    class Logger {
    public:
        /**
         * 必须在程序入口先调用一次
         * 例如: Logger::init();
         */
        static void init();

        /** 返回底层 Boost logger，可自行扩展 */
        static boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>& core() { static boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> lg; return lg; }
        /* ---------- 便捷包装：与宏等价 ---------- */

        template <typename... Args>
        inline static void trace(Args&&... args)   { log(boost::log::trivial::severity_level::trace,   std::forward<Args>(args)...); }
        template <typename... Args>
        inline static void debug(Args&&... args)   { log(boost::log::trivial::severity_level::debug,   std::forward<Args>(args)...); }
        template <typename... Args>
        inline static void info(Args&&... args)    { log(boost::log::trivial::severity_level::info,    std::forward<Args>(args)...); }
        template <typename... Args>
        inline static void warn(Args&&... args)    { log(boost::log::trivial::severity_level::warning, std::forward<Args>(args)...); }
        template <typename... Args>
        inline static void error(Args&&... args)   { log(boost::log::trivial::severity_level::error,   std::forward<Args>(args)...); }
        template <typename... Args>
        inline static void fatal(Args&&... args)   { log(boost::log::trivial::severity_level::fatal,   std::forward<Args>(args)...); }

    private:
        template <typename... Args>
        static void log(boost::log::trivial::severity_level lvl, Args&&... args) {
            std::ostringstream oss;
            (oss << ... << std::forward<Args>(args));           // C++17 折叠表达式
            BOOST_LOG_SEV(core(), lvl) << oss.str();
        }
    };
}// namespace shenshang::logger
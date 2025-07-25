#include "utils/logger.hpp"
#include <boost/log/core/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/current_thread_id.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/log/support/date_time.hpp>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <mutex>

static boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> global_logger;

static std::string get_color(boost::log::trivial::severity_level level) {
    switch (level) {
        case boost::log::trivial::trace: return "\033[36m";
        case boost::log::trivial::debug: return "\033[34m";
        case boost::log::trivial::info: return "\033[32m";
        case boost::log::trivial::warning: return "\033[33m";
        case boost::log::trivial::error: return "\033[31m";
        case boost::log::trivial::fatal: return "\033[41m";
        default: return "\033[0m";
    }
}

std::string get_today_date() {
    std::time_t now = std::time(nullptr);
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&now));
    return std::string(buf);
}

void shenshang::utils::logger::Logger::init() {
    static std::once_flag flag;
    std::call_once(flag, []() {
        boost::log::add_common_attributes();
        auto console_sink = boost::make_shared<boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend>>();

        console_sink->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
        console_sink->set_formatter([](const boost::log::record_view& rec, boost::log::formatting_ostream& strm) {
            auto level = rec[boost::log::trivial::severity].get();
            std::string color = get_color(level);
            std::string reset = "\033[0m";
            auto timestamp = boost::log::extract<boost::posix_time::ptime>("TimeStamp", rec);
            strm << color
                << "[" << boost::posix_time::to_simple_string(timestamp.get()) << "]"
                << "[" << rec[boost::log::trivial::severity] << "]"
                << "[" << boost::log::extract<boost::log::attributes::current_thread_id::value_type>("ThreadID", rec) << "] "
                << rec[boost::log::expressions::smessage]
                << reset;
        });
        console_sink->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
        boost::log::core::get()->add_sink(console_sink);

        std::string date = get_today_date();
        std::string dir_path = "/home/antaresz/Projects/ShenShang/logs/" + date;
        std::filesystem::create_directories(dir_path);

        std::string latest_path = dir_path + "/latest.log";
        auto latest_sink = boost::log::add_file_log(
            boost::log::keywords::file_name = latest_path,
            boost::log::keywords::auto_flush = true,
            boost::log::keywords::open_mode = std::ios_base::out | std::ios_base::trunc,
            boost::log::keywords::format =
                boost::log::expressions::stream
                    << "[" << boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S")
                    << "][" << boost::log::trivial::severity
                    << "][" << boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID")
                    << "] " << boost::log::expressions::smessage
        );
        latest_sink->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);

        std::string history_path = dir_path + "/history.log";
        auto history_sink = boost::log::add_file_log(
            boost::log::keywords::file_name = history_path,
            boost::log::keywords::auto_flush = true,
            boost::log::keywords::open_mode = std::ios_base::out | std::ios_base::app,
            boost::log::keywords::format =
                boost::log::expressions::stream
                    << "[" << boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S")
                    << "][" << boost::log::trivial::severity
                    << "][" << boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID")
                    << "] " << boost::log::expressions::smessage
        );
        history_sink->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
    });
}

static boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>& core() {
    return global_logger;   
}

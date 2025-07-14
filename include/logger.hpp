#pragma once
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

class Logger {
public:
    static void init();

    static boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>& get();
};
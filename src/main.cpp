#include "Elevator.h"

#include <iostream>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

void initializeLogging() {
    logging::add_file_log(
            keywords::file_name = "simulation_output.log",
            keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%"
            );
    logging::add_console_log(
            std::cout,
            keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%"
            );
    logging::core::get()->set_filter(
            logging::trivial::severity >= logging::trivial::debug
            );
    logging::add_common_attributes();
}

/**
 * @brief Main entry point for the program
 */
int main()
{
    initializeLogging();
    BOOST_LOG_TRIVIAL(info) << "Info message!";
    BOOST_LOG_TRIVIAL(debug) << "Debug message!";
    return 0;
}

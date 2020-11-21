#include "ElevatorSimulation.h"

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

/**
 * @brief Initializes the boost trivial logger for the simulation
 */
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
            logging::trivial::severity >= logging::trivial::info
            );
    logging::add_common_attributes();
}

/**
 * @brief Main entry point for the program
 */
int main()
{
    initializeLogging();
    ElevatorSimulation sim1{10, "../input/Mod10_Assignment_Elevators.csv"};
    auto simResults1 = sim1.simulate();
    ElevatorSimulation sim2{5, "../input/Mod10_Assignment_Elevators.csv"};
    auto simResults2 = sim2.simulate();
    double avgWaitTime1 = simResults1->avgWaitTime();
    double avgWaitTime2 = simResults2->avgWaitTime();
    BOOST_LOG_TRIVIAL(info) << "Average wait time for Simulation 1: " << avgWaitTime1;
    BOOST_LOG_TRIVIAL(info) << "Average wait time for Simulation 2: " << avgWaitTime2;
    BOOST_LOG_TRIVIAL(info) << "Percent reduction in wait time: " << 100 * (avgWaitTime1 - avgWaitTime2) / avgWaitTime1 << "%";
    double avgTravelTime1 = simResults1->avgTravelTime();
    double avgTravelTime2 = simResults2->avgTravelTime();
    BOOST_LOG_TRIVIAL(info) << "Average travel time for Simulation 1: " << avgTravelTime1;
    BOOST_LOG_TRIVIAL(info) << "Average travel time for Simulation 2: " << avgTravelTime2;
    BOOST_LOG_TRIVIAL(info) << "Percent reduction in travel time: " << 100 * (avgTravelTime1 - avgTravelTime2) / avgTravelTime1 << "%";
    return 0;
}

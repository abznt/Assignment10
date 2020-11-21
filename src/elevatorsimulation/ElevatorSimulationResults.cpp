#include "ElevatorSimulationResults.h"
#include <boost/log/trivial.hpp>

void ElevatorSimulationResults::addResult(unsigned int waitTime, unsigned int travelTime) {
    _waitTimes.emplace_back(waitTime);
    _travelTimes.emplace_back(travelTime);
    BOOST_LOG_TRIVIAL(info) << "Simulation result added. Total number of results = " << _waitTimes.size();
}

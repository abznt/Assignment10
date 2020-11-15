#include "ElevatorSimulationResults.h"

void ElevatorSimulationResults::addResult(unsigned int waitTime, unsigned int travelTime) {
    _waitTimes.push_back(waitTime);
    _travelTimes.push_back(travelTime);
}

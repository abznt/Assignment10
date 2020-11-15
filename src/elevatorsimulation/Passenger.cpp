#include "Passenger.h"

#include <boost/log/trivial.hpp>
#include <utility>

unsigned int Passenger::_uidCounter = 0;

Passenger::Passenger(const unsigned int arrivalTime, const unsigned int destinationFloor,
                     std::shared_ptr<ElevatorSimulationResults> results) :
        uid{_uidCounter++}, _arrivalTime{arrivalTime}, _destinationFloor{destinationFloor}, _waitTime{0}, _travelTime{0}
{
    _results = results;
    BOOST_LOG_TRIVIAL(debug) << "Created Passsenger with UID = " << uid;
}

void Passenger::startTraveling(unsigned int currentTime)
{
    _waitTime = currentTime - _arrivalTime;
    _travelTime = currentTime;
    BOOST_LOG_TRIVIAL(debug) << "Passenger " << uid << " started traveling at time " << currentTime;
    BOOST_LOG_TRIVIAL(debug) << "Passenger " << uid << " waited for " << _waitTime;
}

void Passenger::stopTraveling(unsigned int currentTime)
{
    _travelTime = currentTime - _travelTime;
    BOOST_LOG_TRIVIAL(debug) << "Passenger " << uid << " traveled for " << _travelTime;
    if (_results)
    {
        _results->addResult(_waitTime, _travelTime);
    }
}





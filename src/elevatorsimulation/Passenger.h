#ifndef ASSIGNMENT2_PASSENGER_H
#define ASSIGNMENT2_PASSENGER_H

#include "ElevatorSimulationResults.h"
#include <memory>

class Passenger {
public:
    const unsigned int uid;

private:
    const unsigned _arrivalTime;
    const unsigned _destinationFloor;
    unsigned _waitTime;
    unsigned _travelTime;
    static unsigned int _uidCounter;
    std::shared_ptr<ElevatorSimulationResults> _results;

public:
    Passenger(unsigned arrivalTime, unsigned destinationFloor, std::shared_ptr<ElevatorSimulationResults> results = nullptr);

    [[nodiscard]] unsigned getArrivalTime() const {
        return _arrivalTime;
    }

    [[nodiscard]] unsigned getDestinationFloor() const {
        return _destinationFloor;
    }

    [[nodiscard]] unsigned getWaitTime() const {
        return _waitTime;
    }

    [[nodiscard]] unsigned getTravelTime() const {
        return _travelTime;
    }

    void startTraveling(unsigned currentTime);
    void stopTraveling(unsigned currentTime);
};


#endif //ASSIGNMENT2_PASSENGER_H

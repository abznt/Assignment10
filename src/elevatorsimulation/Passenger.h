#ifndef ASSIGNMENT2_PASSENGER_H
#define ASSIGNMENT2_PASSENGER_H

#include "ElevatorSimulationResults.h"
#include <memory>

/**
 * @brief Encapsulates a passenger in an elevator simulation
 */
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
    /**
     * @brief Constructs a passenger
     * @param arrivalTime the arrival time of the passenger
     * @param destinationFloor the passenger's destination floor
     * @param results optional shared_ptr to a SimulationResults object
     */
    Passenger(unsigned arrivalTime, unsigned destinationFloor, std::shared_ptr<ElevatorSimulationResults> results = nullptr);

    /**
     * @brief Gets the arrival time of the passenger
     * @return arrival time of the passenger
     */
    [[nodiscard]] unsigned getArrivalTime() const {
        return _arrivalTime;
    }

    /**
     * @brief Gets the destination floor of the passenger
     * @return destination floor of the passenger
     */
    [[nodiscard]] unsigned getDestinationFloor() const {
        return _destinationFloor;
    }

    /**
     * @brief Gets the amount of time the passenger waited before travel started
     * @return time that the passenger waited
     */
    [[nodiscard]] unsigned getWaitTime() const {
        return _waitTime;
    }

    /**
     * @brief Gets the amount of time the passenger spent traveling
     * @return time that the passenger spent traveling
     */
    [[nodiscard]] unsigned getTravelTime() const {
        return _travelTime;
    }

    /**
     * @brief Computes the amount of time the passenger waited and starts a counter for the travel time.
     * @param currentTime current simulation time
     */
    void startTraveling(unsigned currentTime);

    /**
     * @brief Computes the amount of time the passenger traveled for
     * @param currentTime current simulation time
     */
    void stopTraveling(unsigned currentTime);
};


#endif //ASSIGNMENT2_PASSENGER_H

#ifndef ASSIGNMENT2_ELEVATOR_H
#define ASSIGNMENT2_ELEVATOR_H

#include "ElevatorState.h"
#include "Passenger.h"
#include "Floor.h"
#include "Building.h"
#include <memory>
#include <vector>

class Building; // need to pre-declare the Building class

/**
 * @brief Encapsulates an elevator in a building
 */
class Elevator {
public:
    const unsigned uid;

private:
    ElevatorState _curState;
    unsigned _timeInCurState;
    const unsigned _capacity;
    const unsigned _travelTime;
    std::vector<std::unique_ptr<Passenger>> _passengers;
    unsigned _curFloor;
    Building* _building;
    unsigned _simTime;
    int _destinationFloor;
    static unsigned _uidCounter;
    static int _passengersInElevators;
    static constexpr unsigned STOPPING_TIME{2};

public:
    /**
     * @brief Constructs an elevator
     * @param building pointer to the building the elevator resides in
     * @param capacity capacity of the elevator
     * @param travelTime time taken to travel between floors
     * @param curFloor starting floor
     */
    Elevator(Building* building, const unsigned capacity, const unsigned travelTime, const unsigned curFloor = 0);
    ~Elevator();
    Elevator(Elevator&& e) = default; // need to explicitly define move constructor

    /**
     * @brief Performs the simulation logic for a single time step
     */
    void modelTick();

    /**
     * @brief Gets the total number of passengers in all elevators
     * @return total number of passengers in all elevators
     */
    static int numPassengersInElevators() { return _passengersInElevators; }

private:
    /**
     * @brief Determines the closest floor that a passenger can be picked up from
     * @return floor number if there is a passenger that can be picked up. -1 if there are no available passengers.
     */
    int findNearestNewPassenger() const;

    /**
     * @brief Determines the closest floor that a passenger can be dropped off at
     * @return floor number
     */
    unsigned findClosestPassengerDestination() const;

    /**
     * @brief Picks up passengers at the current floor
     */
    void pickupPassengers();

    /**
     * @brief Drops off passengers at the current floor
     */
    void dropoffPassengers();

    /**
     * @brief Determines if passengers can be picked up at the current floor
     * @return true if passengers can be picked up, otherwise, false
     */
    bool canPickupPassengers();

    /**
     * @brief Determines if passengers can be dropped off at the current floor
     * @return true if passengers can be dropped off, otherwise, false
     */
    bool canDropoffPassengers();

    /**
     * @brief Logs the elevator's current passengers
     */
    void logCurrentPassengers();
};


#endif //ASSIGNMENT2_ELEVATOR_H

#ifndef ASSIGNMENT2_BUILDING_H
#define ASSIGNMENT2_BUILDING_H

#include "Floor.h"
#include "Elevator.h"
#include "Passenger.h"
#include <vector>
#include <memory>

class Elevator;

/**
 * @brief Encapsulates a building in an elevator simulation
 */
class Building {
public:
    const unsigned nFloors;
    const unsigned nElevators;

private:
    std::vector<Floor> _floors;
    std::vector<Elevator> _elevators;
    unsigned _simTime;
    static constexpr unsigned ELEVATOR_CAPACITY{8};

public:
    /**
     * @brief Constructs a building
     * @param nFloors number of floors in the building
     * @param nElevators number of elevators in the building
     * @param elevatorTravelTime time required for elevators to travel between floors
     */
    Building(unsigned nFloors, unsigned nElevators, unsigned elevatorTravelTime);

    /**
     * @brief Puts a passenger on a floor
     * @param p pointer to a passenger
     * @param floorNumber floor number to put the passenger on
     */
    void passengerArrivedAtFloor(std::unique_ptr<Passenger> p, unsigned floorNumber);

    /**
     * @brief Performs the simulation logic for a single time step
     */
    void modelTick();


    /**
     * @brief Gets a reference to a floor using its floor number
     * @param floorNumber floor number
     * @return reference to the specified floor
     */
    [[nodiscard]] Floor& floorAt(unsigned floorNumber);

private:
    /**
     * @brief Checks if a floor number is in bounds
     * @param floorNumber floor number
     * @return true if the floor number is less than the number of floors in the building and greater than 0, otherwise, false
     */
    [[nodiscard]] bool inBounds(unsigned floorNumber) const;
};


#endif //ASSIGNMENT2_BUILDING_H

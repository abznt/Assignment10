#ifndef ASSIGNMENT2_FLOOR_H
#define ASSIGNMENT2_FLOOR_H

#include "Passenger.h"
#include <queue>
#include <vector>
#include <memory>

/**
 * @brief Encapsulates a floor in a building that can queue passengers waiting for an elevator
 */
class Floor {
private:
    const unsigned _floorNumber;
    std::queue<std::unique_ptr<Passenger>> _passengerQueue;
    static int _passengersOnFloors;

public:
    /**
     * @brief Default constructor. Assigns a number to a floor.
     * @param floorNumber number of the floor
     */
    explicit Floor(unsigned floorNumber);

    /**
     * @brief Move constructor.
     * @param floor
     */
    Floor(Floor&& floor) = default;

    /**
     * @brief Represents the event where a passenger arrives at a floor. Transfers ownership of the passenger to the floor.
     * @param p pointer to the passenger
     */
    void passengerArrived(std::unique_ptr<Passenger> p);

    /**
     * @brief Represents the event where a passenger departs from a floor. Transfers ownership of the passenger away from the floor.
     * @param departureTime time the passenger departs from the floor
     * @return pointer to the passenger
     */
    std::unique_ptr<Passenger> passengerDeparted(unsigned departureTime);

    /**
     * @brief Gets the number of passengers queued on a floor
     * @return the number of passengers on the floor
     */
    [[nodiscard]] size_t nPassengersWaiting() const;

    /**
     * @brief Determines if the floor has passengers
     * @return True if no passengers. False otherwise.
     */
    [[nodiscard]] bool empty() const;

    /**
     * @brief Gets the total number of passengers on all floors
     * @return total number of passengers on all floors
     */
    static int numPassengersOnFloors() { return _passengersOnFloors; }
};


#endif //ASSIGNMENT2_FLOOR_H

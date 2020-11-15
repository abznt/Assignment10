#ifndef ASSIGNMENT2_FLOOR_H
#define ASSIGNMENT2_FLOOR_H

#include "Passenger.h"
#include "ArrivalTimePriority.h"
#include <queue>
#include <vector>
#include <memory>

class Floor {
private:
    const unsigned _floorNumber;
    std::queue<std::unique_ptr<Passenger>> _passengerQueue;

public:
    Floor(unsigned floorNumber);

    void passengerArrived(std::unique_ptr<Passenger> p);

    std::unique_ptr<Passenger> passengerDeparted();
};


#endif //ASSIGNMENT2_FLOOR_H

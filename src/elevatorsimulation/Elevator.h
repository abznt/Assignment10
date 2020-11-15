#ifndef ASSIGNMENT2_ELEVATOR_H
#define ASSIGNMENT2_ELEVATOR_H

#include "ElevatorState.h"
#include "Passenger.h"
#include "Floor.h"
#include <memory>
#include <vector>

class Elevator {
private:
    ElevatorState _curState;
    unsigned timeInCurState;
    const unsigned _capacity;
    const unsigned _travelTime;
    std::vector<std::unique_ptr<Passenger>> _passengers;
    unsigned _curFloor;

public:
    Elevator(unsigned capacity, unsigned travelTime, unsigned _curFloor = 0);
};


#endif //ASSIGNMENT2_ELEVATOR_H

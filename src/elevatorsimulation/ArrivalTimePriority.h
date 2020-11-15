#ifndef ASSIGNMENT2_ARRIVALTIMEPRIORITY_H
#define ASSIGNMENT2_ARRIVALTIMEPRIORITY_H

#include "Passenger.h"
#include <memory>

struct ArrivalTimePriority {
    bool operator()(std::unique_ptr<Passenger> p1, std::unique_ptr<Passenger> p2) {
        return p1->getArrivalTime() < p2->getArrivalTime();
    }
};

#endif //ASSIGNMENT2_ARRIVALTIMEPRIORITY_H

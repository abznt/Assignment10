#include "Building.h"
#include <stdexcept>
#include <boost/log/trivial.hpp>

Building::Building(unsigned nFloors, unsigned nElevators, unsigned elevatorTravelTime)
        : nFloors{nFloors}, nElevators{nElevators}, _simTime{0} {
    for (unsigned i = 0; i < nFloors; ++i) {
        _floors.emplace_back(i);
    }
    for (unsigned i = 0; i < nElevators; ++i) {
        _elevators.emplace_back(this, ELEVATOR_CAPACITY, elevatorTravelTime, 0);
    }
}

void Building::passengerArrivedAtFloor(std::unique_ptr<Passenger> p, const unsigned floorNumber) {
    if (inBounds(floorNumber)) {
        _floors.at(floorNumber).passengerArrived(std::move(p));
    }
    else {
        BOOST_LOG_TRIVIAL(error) << "Floor number is out of bounds";
        throw std::runtime_error("Floor number is out of bounds");
    }
}

void Building::modelTick() {
    for (auto &elevator : _elevators) {
        elevator.modelTick();
    }
    ++_simTime;
}

Floor &Building::floorAt(const unsigned floorNumber) {
    if (inBounds(floorNumber)) {
        return _floors.at(floorNumber);
    }
    else {
        BOOST_LOG_TRIVIAL(error) << "Floor number is out of bounds";
        throw std::runtime_error("Floor number is out of bounds");
    }
}

bool Building::inBounds(const unsigned floorNumber) const {
    if (floorNumber >= 0 && floorNumber < nFloors) {
        return true;
    }
    else {
        return false;
    }
}


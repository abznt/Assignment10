#include "Elevator.h"
#include <boost/log/trivial.hpp>
#include <memory>
#include <stdexcept>
#include <cmath>

unsigned Elevator::_uidCounter = 0;
int Elevator::_passengersInElevators = 0;

Elevator::Elevator(Building* building, const unsigned capacity, const unsigned travelTime, const unsigned curFloor) :
        _capacity{capacity}, _travelTime{travelTime}, _curFloor{curFloor}, _timeInCurState{0}, _destinationFloor{0},
        _curState{ElevatorState::STOPPED}, uid{_uidCounter++}, _building{building}, _simTime{0} {
    BOOST_LOG_TRIVIAL(debug) << "Created elevator number " << uid << " with capacity = " << _capacity <<
        " travel time = " << _travelTime;
}

Elevator::~Elevator() {
    _building = nullptr;
}

void Elevator::modelTick() {
    switch (_curState) {
        case (ElevatorState::STOPPED) :
            // Elevator is stopped at a floor
            if (!_passengers.empty()) {
                // Drop off passengers if the elevator has any
                dropoffPassengers();
            }
            pickupPassengers();
            // Update destination if needed
            if (_destinationFloor == -1 || _destinationFloor == (int)_curFloor) {
                // Find a new destination floor
                if (!_passengers.empty()) {
                    // Find new destination based on current passengers
                    _destinationFloor = (int)findClosestPassengerDestination();
                }
                else {
                    // Look for a passenger waiting at the closest floor
                    _destinationFloor = findNearestNewPassenger();
                }
            }
            // Determine the elevator's next state
            if (_destinationFloor == -1) {
                // No destination was found
                _timeInCurState++;
                BOOST_LOG_TRIVIAL(debug) << "Elevator " << uid << " is remaining stopped at Floor " << _curFloor;
            }
            else {
                // A new destination was found, compute the direction
                if (_destinationFloor - (int)_curFloor > 0) {
                    // Destination floor is above the current floor
                    _curState = ElevatorState::MOVING_UP;
                    _timeInCurState = 0;
                    BOOST_LOG_TRIVIAL(debug) << "Elevator " << uid << " is moving up. Destination Floor is " << _destinationFloor;
                } else {
                    // Destination floor is below the current floor
                    _curState = ElevatorState::MOVING_DOWN;
                    _timeInCurState = 0;
                    BOOST_LOG_TRIVIAL(debug) << "Elevator " << uid << " is moving down. Destination Floor is " << _destinationFloor;
                }
            }
            break;
        case (ElevatorState::MOVING_DOWN) :
            // Elevator is moving down
            if (_timeInCurState < _travelTime - 1) {
                // Elevator is still moving to a new floor
                ++_timeInCurState;
                BOOST_LOG_TRIVIAL(debug) << "Elevator " << uid << " is moving down from Floor " << _curFloor;
            }
            else {
                // Elevator has reached a new floor
                _curFloor--;
                _timeInCurState = 0;
                if (canDropoffPassengers() || canPickupPassengers()) {
                    // Change state to STOPPING
                    _curState = ElevatorState::STOPPING;
                    BOOST_LOG_TRIVIAL(debug) << "Elevator " << uid << " is stopping at Floor " << _curFloor;
                }
                else if (_curFloor == 0) {
                    // Emergency stopping condition
                    _curState = ElevatorState::STOPPING;
                    _destinationFloor = -1;
                    BOOST_LOG_TRIVIAL(warning) << "Elevator " << uid << " is making an emergency stop";
                }
            }
            break;
        case (ElevatorState::MOVING_UP) :
            // Elevator is moving up
            if (_timeInCurState < _travelTime - 1) {
                // Elevator is still moving to a new floor
                ++_timeInCurState;
                BOOST_LOG_TRIVIAL(debug) << "Elevator " << uid << " is moving up from Floor " << _curFloor;
            }
            else {
                _curFloor++;
                _timeInCurState = 0;
                if (canDropoffPassengers() || canPickupPassengers()) {
                    // Change state to STOPPING
                    _curState = ElevatorState::STOPPING;
                    BOOST_LOG_TRIVIAL(debug) << "Elevator " << uid << " is stopping at Floor " << _curFloor;
                }
                else if (_curFloor == _building->nFloors - 1) {
                    // Emergency stopping condition
                    _curState = ElevatorState::STOPPING;
                    _destinationFloor = -1;
                    BOOST_LOG_TRIVIAL(warning) << "Elevator " << uid << " is making an emergency stop";
                }
            }
            break;
        case (ElevatorState::STOPPING) :
            // Elevator is stopping
            if (_timeInCurState < STOPPING_TIME - 1) {
                // Elevator is still stopping
                _timeInCurState++;
            }
            else {
                // Change state to STOPPED
                _curState = ElevatorState::STOPPED;
                _timeInCurState = 0;
                BOOST_LOG_TRIVIAL(debug) << "Elevator " << uid << " has stopped at Floor " << _curFloor;
            }
            break;
        default :
            throw std::runtime_error("Unknown ElevatorState");
    }
    ++_simTime; // increment the simulation time
}

int Elevator::findNearestNewPassenger() const {
    bool noWaitingPassengers = true;
    int currentMin = INT_MAX;
    int closestFloor;
    for (size_t i = 0; i < _building->nFloors; ++i) {
        if (!_building->floorAt(i).empty()) {
            noWaitingPassengers = false;
            int newMin = std::abs((int)_curFloor - (int)i);
            if (newMin < currentMin) {
                currentMin = newMin;
                closestFloor = i;
            }
        }
    }
    if (noWaitingPassengers) {
        return -1;
    }
    else {
        return closestFloor;
    }
}

unsigned Elevator::findClosestPassengerDestination() const {
    unsigned currentMin = UINT_MAX;
    unsigned closestFloor;
    for (auto &p : _passengers) {
        unsigned newMin = std::abs((int)_curFloor - (int)p->getDestinationFloor());
        if (newMin < currentMin) {
            currentMin = newMin;
            closestFloor = p->getDestinationFloor();
        }
    }
    return closestFloor;
}

void Elevator::pickupPassengers() {
    // Only load passengers while the elevator is not at capacity and the floor isn't emtpy
    while (canPickupPassengers()) {
        auto p = _building->floorAt(_curFloor).passengerDeparted(_simTime);
        BOOST_LOG_TRIVIAL(debug) << "Loading Passenger " << p->uid << " onto Elevator " << uid  << " at t = " << _simTime;
        _passengers.push_back(std::move(p));
        _passengersInElevators++;
    }
}

void Elevator::dropoffPassengers() {
    logCurrentPassengers();
    size_t n = _passengers.size();
    for (size_t i = n - 1; i < n; --i) {
        if (_passengers.at(i)->getDestinationFloor() == _curFloor) {
            _passengers.at(i)->stopTraveling(_simTime);
            BOOST_LOG_TRIVIAL(debug) << "Dropping off Passenger " << _passengers.at(i)->uid << " at Floor " << _curFloor
                                     << " from Elevator " << uid;
            _passengers.erase(_passengers.begin() + i);
            _passengersInElevators--;
        }
    }
//    for (auto &passenger : _passengers) {
//        if (passenger->getDestinationFloor() == _curFloor) {
//            passenger->stopTraveling(_simTime);
//            BOOST_LOG_TRIVIAL(debug) << "Dropping off Passenger " << passenger->uid << " at Floor " << _curFloor
//                << " from Elevator " << uid;
//            _passengersInElevators--;
//        }
//    }
//    _passengers.erase(
//            std::remove_if(
//                    _passengers.begin(), _passengers.end(),
//                    [this](std::unique_ptr<Passenger> &p){return p->getDestinationFloor() == _curFloor;}
//                    ), _passengers.end());
    logCurrentPassengers();
}

bool Elevator::canPickupPassengers() {
    if (_passengers.size() < _capacity && !_building->floorAt(_curFloor).empty()) {
        return true;
    }
    else {
        return false;
    }
}

bool Elevator::canDropoffPassengers() {
    return std::any_of(
            _passengers.begin(), _passengers.end(),
            [this](std::unique_ptr<Passenger> &p){return p->getDestinationFloor() == _curFloor;}
            );
}

void Elevator::logCurrentPassengers() {
    BOOST_LOG_TRIVIAL(trace) << "Current passengers on Elevator " << uid;
    for (auto &passenger : _passengers) {
        BOOST_LOG_TRIVIAL(trace) << "\tPassenger " << passenger->uid;
    }
}



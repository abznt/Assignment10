#include "Floor.h"
#include <sstream>
#include <exception>
#include <boost/log/trivial.hpp>

int Floor::_passengersOnFloors = 0;

Floor::Floor(unsigned floorNumber) : _floorNumber{floorNumber} {
    BOOST_LOG_TRIVIAL(debug) << "Created floor number " << floorNumber;
}

void Floor::passengerArrived(std::unique_ptr<Passenger> p) {
    BOOST_LOG_TRIVIAL(info) << "Passenger " << p->uid << " is waiting at Floor " << _floorNumber;
    // Transfer ownership of the passenger to the Floor
    _passengerQueue.push(std::move(p));
    _passengersOnFloors++;
}

std::unique_ptr<Passenger> Floor::passengerDeparted(unsigned departureTime) {
    if (!_passengerQueue.empty()) {
        auto tmp = std::move(_passengerQueue.front());
        _passengerQueue.pop();
        BOOST_LOG_TRIVIAL(info) << "Passenger " << tmp->uid << " is departing Floor " << _floorNumber;
        tmp->startTraveling(departureTime);
        _passengersOnFloors--;
        return std::move(tmp);
    }
    else {
        std::stringstream err;
        err << "No passengers on Floor " << _floorNumber;
        BOOST_LOG_TRIVIAL(error) << err.str();
        throw std::runtime_error(err.str());
    }
}

size_t Floor::nPassengersWaiting() const {
    return _passengerQueue.size();
}

bool Floor::empty() const {
    return _passengerQueue.empty();
}

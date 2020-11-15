#include "Floor.h"
#include <sstream>
#include <exception>
#include <boost/log/trivial.hpp>

Floor::Floor(unsigned floorNumber) : _floorNumber{floorNumber} {}

void Floor::passengerArrived(std::unique_ptr<Passenger> p) {
    // Transfer ownership of the passenger to the Floor
    BOOST_LOG_TRIVIAL(debug) << "Passenger " << p->uid << " is waiting at Floor " << _floorNumber;
    _passengerQueue.push(std::move(p));
}

std::unique_ptr<Passenger> Floor::passengerDeparted() {
    if (!_passengerQueue.empty()) {
        auto tmp = std::move(_passengerQueue.front());
        _passengerQueue.pop();
        BOOST_LOG_TRIVIAL(debug) << "Passenger " << tmp->uid << " is departing Floor " << _floorNumber;
        return std::move(tmp);
    }
    else {
        std::stringstream err;
        err << "No passengers on Floor " << _floorNumber;
        BOOST_LOG_TRIVIAL(error) << err.str();
        throw std::runtime_error(err.str());
    }
}

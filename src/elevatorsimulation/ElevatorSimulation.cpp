#include "ElevatorSimulation.h"
#include <fstream>
#include <sstream>
#include <boost/log/trivial.hpp>

ElevatorSimulation::ElevatorSimulation(unsigned elevatorTravelTime, const std::string& inputFile) :
        _building{100, 4, elevatorTravelTime}, _simTime{0} {
    _results = std::make_shared<ElevatorSimulationResults>();
    loadInputFile(inputFile);
    _nPassengers = _passengerQueueInput.size();
}

std::shared_ptr<ElevatorSimulationResults> ElevatorSimulation::simulate() {
    BOOST_LOG_TRIVIAL(info) << "Starting elevator simulation";
    while (!stoppingCondition()) {
        if (_simTime % 10 == 0) {
            BOOST_LOG_TRIVIAL(info) << "Simulation time = " << _simTime;
            BOOST_LOG_TRIVIAL(info) << "Passengers on elevators = " << Elevator::numPassengersInElevators()
                << ", Passengers on floors = " << Floor::numPassengersOnFloors();
        }
        else {
            BOOST_LOG_TRIVIAL(trace) << "Simulation time = " << _simTime;
        }
        while (!_passengerQueueInput.empty() && _passengerQueueInput.front().second->getArrivalTime() == _simTime) {
            auto tmp = std::move(_passengerQueueInput.front());
            _passengerQueueInput.pop();
            _building.floorAt(tmp.first).passengerArrived(std::move(tmp.second));
        }
        _building.modelTick();
        _simTime++;
    }
    BOOST_LOG_TRIVIAL(info) << "Elevator simulation finished";
    return _results;
}

bool ElevatorSimulation::stoppingCondition() const {
    if (_results->numResults() < _nPassengers && _simTime < 20000) {
        return false;
    }
    else {
        return true;
    }
}

void ElevatorSimulation::loadInputFile(const std::string &inputFile) {
    std::ifstream csvFile(inputFile);
    if (!csvFile.is_open()) {
        throw std::runtime_error("Could not open input file!");
    }
    std::string line;
    int startingFloor, destinationFloor, arrivalTime;
    // Discard the first line
    if (csvFile.good()) std::getline(csvFile, line);
    // Read data line by line
    while(std::getline(csvFile, line)) {
        std::stringstream ss(line);
        ss >> arrivalTime;
        if (ss.peek() == ',') ss.ignore();
        ss >> startingFloor;
        if (ss.peek() == ',') ss.ignore();
        ss >> destinationFloor;
        // subtract 1 from floor number so that it starts at floor 0
        _passengerQueueInput.push(std::make_pair(startingFloor - 1,
                                                 std::make_unique<Passenger>(arrivalTime, destinationFloor - 1, _results)));
    }
    csvFile.close();
}

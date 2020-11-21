#ifndef ASSIGNMENT2_ELEVATORSIMULATION_H
#define ASSIGNMENT2_ELEVATORSIMULATION_H

#include "Building.h"
#include "ElevatorSimulationResults.h"
#include <memory>
#include <string>

/**
 * @brief Main driver code for the elevator simulation
 */
class ElevatorSimulation {
private:
    Building _building;
    std::shared_ptr<ElevatorSimulationResults> _results;
    std::queue<std::pair<int, std::unique_ptr<Passenger>>> _passengerQueueInput;
    size_t _nPassengers;
    unsigned _simTime;

public:
    /**
     * @brief Creates an elevator simulation
     * @param elevatorTravelTime time required for elevators to travel between floors
     * @param inputFile input csv file containing the passenger arrival times, arrival floors, and destination floors
     */
    ElevatorSimulation(unsigned elevatorTravelTime, const std::string& inputFile);

    /**
     * @brief Runs the elevator simulation
     * @return pointer to the simulation results
     */
    std::shared_ptr<ElevatorSimulationResults> simulate();

private:
    /**
     * @brief Evaluates the stopping condition for the simulation
     * @return true if the simulation should stop, otherwise, false
     */
    [[nodiscard]] bool stoppingCondition() const;

    /**
     * @brief Utility function to parse a csv file into a passenger queue
     * @param inputFile input csv file containing the passenger arrival times, arrival floors, and destination floors
     */
    void loadInputFile(const std::string &inputFile);
};


#endif //ASSIGNMENT2_ELEVATORSIMULATION_H

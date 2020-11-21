#ifndef ASSIGNMENT2_ELEVATORSIMULATIONRESULTS_H
#define ASSIGNMENT2_ELEVATORSIMULATIONRESULTS_H

#include <vector>
#include <numeric>
/**
 * @brief Used to store passenger wait and travel times for an ElevatorSimulation.
 */
class ElevatorSimulationResults {
private:
    std::vector<unsigned> _waitTimes;
    std::vector<unsigned> _travelTimes;

public:
    /**
     * @brief Stores data points for wait time and travel time
     * @param waitTime passenger wait time
     * @param travelTime passenger travel time
     */
    void addResult(unsigned int waitTime, unsigned int travelTime);

    /**
     * @return total number of data points being stored
     */
    [[nodiscard]] size_t numResults() const {
        return _waitTimes.size();
    }

    /**
     * @brief Computes the average wait time for the current data set
     * @return average wait time
     */
    [[nodiscard]] double avgWaitTime() const {
        return 1.0 * std::accumulate(_waitTimes.begin(), _waitTimes.end(), 0LL) / _waitTimes.size();
    }

    /**
     * @brief Computes the average travel time for the current data set
     * @return average travel time
     */
    [[nodiscard]] double avgTravelTime() const {
        return 1.0 * std::accumulate(_travelTimes.begin(), _travelTimes.end(), 0LL) / _travelTimes.size();
    }
};


#endif //ASSIGNMENT2_ELEVATORSIMULATIONRESULTS_H

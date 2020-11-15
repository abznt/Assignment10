#ifndef ASSIGNMENT2_ELEVATORSIMULATIONRESULTS_H
#define ASSIGNMENT2_ELEVATORSIMULATIONRESULTS_H

#include <vector>

class ElevatorSimulationResults {
private:
    std::vector<unsigned int> _waitTimes;
    std::vector<unsigned int> _travelTimes;

public:
    void addResult(unsigned int waitTime, unsigned int travelTime);
};


#endif //ASSIGNMENT2_ELEVATORSIMULATIONRESULTS_H

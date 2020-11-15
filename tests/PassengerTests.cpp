#include "gtest/gtest.h"
#include "Passenger.h"
#include <vector>

class PassengerTests : public ::testing::Test {
protected:
    void SetUp() override {
        arrivalTimes.insert(arrivalTimes.end(), {5, 20, 40, 60});
        pickupTimes.insert(pickupTimes.end(), {10, 25, 57, 80});
        dropoffTimes.insert(dropoffTimes.end(), {15, 29, 64, 94});
        destinations.insert(destinations.end(), {2, 5, 7, 22});
    }

    std::vector<unsigned int> arrivalTimes;
    std::vector<unsigned int> pickupTimes;
    std::vector<unsigned int> dropoffTimes;
    std::vector<unsigned int> destinations;
    const size_t NUM_TESTS{4};
};


TEST_F(PassengerTests, TestConstructor) {
    for (size_t i = 0; i < NUM_TESTS; ++i) {
        Passenger p{arrivalTimes.at(i), destinations.at(i)};
        ASSERT_EQ(p.getArrivalTime(), arrivalTimes.at(i));
        ASSERT_EQ(p.getDestinationFloor(), destinations.at(i));
        ASSERT_EQ(p.uid, i);
    }
}

TEST_F(PassengerTests, TestWaitTime) {
    for (size_t i = 0; i < NUM_TESTS; ++i) {
        Passenger p{arrivalTimes.at(i), destinations.at(i)};
        p.startTraveling(pickupTimes.at(i));
        EXPECT_EQ(p.getWaitTime(), pickupTimes.at(i) - arrivalTimes.at(i));
    }
}

TEST_F(PassengerTests, TestTravelTime) {
    for (size_t i = 0; i < NUM_TESTS; ++i) {
        Passenger p{arrivalTimes.at(i), destinations.at(i)};
        p.startTraveling(pickupTimes.at(i));
        p.stopTraveling(dropoffTimes.at(i));
        EXPECT_EQ(p.getTravelTime(), dropoffTimes.at(i) - pickupTimes.at(i));
    }
}
set(libname elevatorsimulation)

set(sources
        Elevator.cpp
        Elevator.h
        Passenger.cpp
        Passenger.h
        ElevatorSimulationResults.cpp
        ElevatorSimulationResults.h
        ElevatorState.h
        ArrivalTimePriority.h Floor.cpp Floor.h Building.cpp Building.h)

add_library(${libname} STATIC ${sources})
target_include_directories(${libname} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${libname} Boost::log)

unset(${libname})
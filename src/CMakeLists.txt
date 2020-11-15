set(targetName Main)
project(${targetName})

find_package(Boost 1.74 COMPONENTS log log_setup REQUIRED)

add_subdirectory(elevatorsimulation)

add_executable(${targetName} main.cpp)
target_link_libraries(${targetName} Boost::log Boost::log_setup elevatorsimulation)

unset(targetName)
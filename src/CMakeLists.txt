set(targetName Main)
project(${targetName})

set(Boost_DEBUG 1)
find_package(Boost COMPONENTS log log_setup REQUIRED)

add_subdirectory(elevatorsimulation)

add_executable(${targetName} main.cpp)
target_link_libraries(${targetName} Boost::log Boost::log_setup elevatorsimulation)

install(TARGETS ${targetName} DESTINATION ${CMAKE_BINARY_DIR}/bin)
add_custom_command(TARGET ${targetName} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/input/Mod10_Assignment_Elevators.csv ${CMAKE_BINARY_DIR}/input)

unset(targetName)
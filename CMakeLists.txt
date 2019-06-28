cmake_minimum_required(VERSION 3.14)
project(elevator_proj)

set(CMAKE_CXX_STANDARD 14)

add_executable(elevator_proj main.cpp elevator/elevator.cpp elevator/elevator.h elevator/elevatorState.h control_panel/controlPanel.h)

# Create logs directory
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")
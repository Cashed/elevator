#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <queue>
#include <signal.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "elevator/elevator.h"

const int DELAY = 1000;
const int MIN_FLOOR = 1;
const int MAX_FLOOR = 10;

static volatile bool elevatorOn = true;

void sigHandler(int sig) {
    spdlog::info("Elevator shutting down!");
    elevatorOn = false;
}

void addPersonWaiting(std::vector<int> &building, const int floor) {
    if (building[floor] > 3) {
        return;
    }
    building[floor] += 1;
}

int getRandomFloor(const int minValue, const int maxValue) {
   return rand() % maxValue + minValue;
}

int main() {
    std::vector<int> building(MAX_FLOOR + 1);

    for (auto i = 1; i <= MAX_FLOOR; ++i) {
        building[i] = 0;
    }

    std::srand(time(nullptr));

    elevator elevator(MAX_FLOOR, MIN_FLOOR);

    spdlog::info("Elevator ready!");

    signal(SIGINT, sigHandler);

    while (elevatorOn) {
        auto startTime = time(nullptr);
        auto personIsWaiting = rand() % 2 == 0;

        if (personIsWaiting) {
            auto currentFloor = getRandomFloor(MIN_FLOOR, MAX_FLOOR);

            addPersonWaiting(building, currentFloor);

            // do they push the up or down button?
            ElevatorState directionRequest;

            if (rand() % 2 == 0) {
                directionRequest = UP;
            } else {
                directionRequest = DOWN;
            }

            elevator.acceptRequest(request(currentFloor, directionRequest));
        }

        elevator.handlePassengers(building);

        std::this_thread::sleep_for(std::chrono::milliseconds(startTime + DELAY - time(nullptr)));
    }

    for (auto el : building) {
        std::cout << el << " ";
    }


    return 0;
}

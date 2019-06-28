#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <signal.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "elevator/elevator.h"

const int DELAY = 500;
const int MIN_FLOOR = 1;
const int MAX_FLOOR = 10;

static volatile bool elevatorOn = true;

void sigHandler(int sig) {
    spdlog::info("Elevator shutting down!");
    elevatorOn = false;
}

int main() {
    elevator elevator(MIN_FLOOR, MAX_FLOOR);

    std::vector<bool> reqs = { false, true, true, false, false, true, false, false, true, true, true };

    elevator.acceptRequest(2, UP);
    elevator.acceptRequest(5, DOWN);
    elevator.acceptRequest(1, UP);
    elevator.acceptRequest(9, UP);
    elevator.acceptRequest(10, DOWN);

    while (elevatorOn) {
        if (reqs[elevator.CurrentFloor()]) {
            auto destination = (rand() % 10) + 1;
            std::cout << "pushing floor number " << destination << std::endl;
            elevator.pushFloorNum(destination);
        }

        elevator.run();
    }


    return 0;
}

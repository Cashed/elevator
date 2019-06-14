#ifndef ELEVATOR_PROJ_REQUEST_H
#define ELEVATOR_PROJ_REQUEST_H

#include "elevator/elevatorState.h"

class request {
public:
    request() = delete;
    request(const int currentFloor, const ElevatorState direction):
            _currentFloor(currentFloor), _direction(direction){}

    int CurrentFloor() const { return _currentFloor; };
    ElevatorState Direction() const { return _direction; };
private:
    int _currentFloor = 1;
    ElevatorState _direction = UP;
};

#endif //ELEVATOR_PROJ_REQUEST_H

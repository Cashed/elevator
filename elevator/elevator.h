#ifndef ELEVATOR_PROJ_ELEVATOR_H
#define ELEVATOR_PROJ_ELEVATOR_H

#include "elevatorState.h"
#include "../request.h"
#include <vector>
#include <queue>

class elevator {
public:
    elevator() = delete;
    elevator(int maxFloor);
    elevator(int maxFloor, int minFloor);
    int MaxFloor() const { return _maxFloor; };
    int MinFloor() const { return _minFloor; };
    int CurrentFloor() const { return _currentFloor; };
    ElevatorState CurrentDirection() const { return _currentDirection; }
    std::vector<std::queue<ElevatorState>> FloorRequests() const { return _floorRequests; };

    void acceptRequest(const request &request);
    void handlePassengers();
private:
    int _maxFloor = 10;
    int _minFloor = 1;
    int _currentFloor = 1;
    ElevatorState _currentDirection = IDLE;
    std::vector<std::queue<ElevatorState>> _floorRequests;
    int _destinationRequests[10];

    void _moveUp();
    void _moveDown();
    void _createRequestQueue();
    bool _isValidPickup();
    void _pickupPassenger();
};


#endif //ELEVATOR_PROJ_ELEVATOR_H

#include "elevator.h"
#include <iostream>
#include <string>

elevator::elevator(const int maxFloor, const int minFloor) {
    _minFloor = minFloor;
    _maxFloor = maxFloor;

    _createRequestQueue();
}

elevator::elevator(const int maxFloor) {
    _minFloor = 1;
    _maxFloor = maxFloor;

    _createRequestQueue();
}

void elevator::acceptRequest(const request &request) {
    if (request.CurrentFloor() >= _minFloor) {
        _floorRequests[request.CurrentFloor()].push(request.Direction());

        std::string direction;

        switch (request.Direction()) {
            case 0 : direction = "UP";
                break;
            case 1 : direction = "DOWN";
                break;
            default : direction = "IDLE";
                break;
        }
        std::cout << "Passenger on floor " << request.CurrentFloor()
                  << " waiting to go " << direction << std::endl;
    }
}

void elevator::handlePassengers() {
    if (!_floorRequests[_currentFloor].empty() && _isValidPickup()) {
        _pickupPassenger();
    } else if (){
        _moveUp();
    }
}

bool elevator::_isValidPickup() {
    return _floorRequests[_currentFloor].front() == _currentDirection ||
        _currentDirection == IDLE;
}

void elevator::_pickupPassenger() {

}

void elevator::_createRequestQueue() {
    _floorRequests.emplace_back(std::queue<ElevatorState>());

    for (auto i = _minFloor; i <= _maxFloor; ++i) {
        _floorRequests.emplace_back(std::queue<ElevatorState>());
    }
}

void elevator::_moveUp() {
    if (_currentFloor < _maxFloor) {
        ++_currentFloor;
    } else {
        _currentDirection = IDLE;
    }
}

void elevator::_moveDown() {
    if (_currentFloor > _minFloor) {
        --_currentFloor;
    } else {
        _currentDirection = IDLE;
    }
}






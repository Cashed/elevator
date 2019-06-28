#include "elevator.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>

elevator::elevator(const int minFloor, const int maxFloor) {
    _minFloor = minFloor;
    _maxFloor = maxFloor;

    _createRequestQueues();
}

elevator::elevator(const int maxFloor) {
    _minFloor = 1;
    _maxFloor = maxFloor;

    _createRequestQueues();
}

void elevator::_createRequestQueues() {
    for (auto i = 0; i <= _maxFloor; ++i) {
        _pickups.emplace_back(false);
        _dropOffs.emplace_back(false);
        _directionReqs.emplace_back(IDLE);
    }
}

void elevator::acceptRequest(const int current, const Direction direction) {
    if (current >= MinFloor() && current <= _maxFloor) {
        _pickups[current] = true;
        _directionReqs[current] = direction;
        
        if (_currentDirection == IDLE) {
            _currentDirection = direction;   
        }
    }
}

void elevator::pushFloorNum(const int destination) {
    if (destination >= _minFloor && destination <= _maxFloor
        && destination != _currentFloor) {
        _dropOffs[destination] = true;
    }
}

void idle() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void elevator::_wait() {
    std::cout << "stopped" << std::endl;
    _stopped = true;
    idle();
    _stopped = false;
}

void elevator::run() {
    if (_pickups[_currentFloor] && _directionReqs[_currentFloor] == _currentDirection) {
        _pickups[_currentFloor] = false;
        _dropOffs[_currentFloor] = false;
        _directionReqs[_currentFloor] = IDLE;

        std::cout << "picking up/dropping off passenger on " << _currentFloor << std::endl;

        _wait();
    } else if (_dropOffs[_currentFloor]) {
        _dropOffs[_currentFloor] = false;

        std::cout << "dropping off passenger on " << _currentFloor << std::endl;

        _wait();
    }

    _move();
    idle();
}


void elevator::_move() {
    if ( _currentDirection == UP) {
        if (_currentFloor < _maxFloor) {
            ++_currentFloor;
            
            std::cout << "moving up to floor " << _currentFloor << std::endl;
        } else {
            _currentDirection = DOWN;
            --_currentFloor;

            std::cout << "reached the top! moving down to floor " << _currentFloor << std::endl;
        }
    } else  {
        if (_currentFloor > _minFloor) {
            --_currentFloor;
            std::cout << "moving down to floor " << _currentFloor << std::endl;

        } else {
            _currentDirection = UP;
            ++_currentFloor;
            std::cout << "reached the bottom! moving up to floor " << _currentFloor << std::endl;
        }
    }
}






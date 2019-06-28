#ifndef ELEVATOR_PROJ_ELEVATOR_H
#define ELEVATOR_PROJ_ELEVATOR_H

#include "elevatorState.h"
#include <vector>
#include <queue>

class elevator {
public:
    elevator() = delete;
    elevator(int maxFloor);
    elevator(int minFloor, int maxFloor);
    int MaxFloor() const { return _maxFloor; };
    int MinFloor() const { return _minFloor; };
    int CurrentFloor() const { return _currentFloor; };
    bool Stopped() const { return _stopped; };
    Direction CurrentDirection() const { return _currentDirection; };
    std::vector<bool> Pickups() const { return _pickups; };
    std::vector<bool> DropOffs() const { return _dropOffs; };
    std::vector<Direction> DirectionReqs() const { return _directionReqs; };

    void acceptRequest(int current, Direction direction);
    void pushFloorNum(int destination);
    void run();
private:
    int _maxFloor = 10;
    int _minFloor = 1;
    int _currentFloor = 1;
    bool _stopped = true;
    Direction _currentDirection = IDLE;
    std::vector<bool> _pickups;
    std::vector<bool> _dropOffs;
    std::vector<Direction> _directionReqs;

    void _createRequestQueues();
    void _move();

    void _wait();
};


#endif //ELEVATOR_PROJ_ELEVATOR_H

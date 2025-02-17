#include "BackTraking.h"

void BackTraking::startBackTraking(sf::RenderWindow& app, Maze& maze) {

    unitPosition_ = maze.getStartPosition();
    isInFinish_ = false;

    std::vector<std::vector<int>> temp(maze.getMazeSize(), std::vector<int> (maze.getMazeSize(), 0));
    isVisited_ = temp;

    clearAction();

    backTraking(app, maze);
}

void BackTraking::backTraking(sf::RenderWindow& app, Maze& maze) {

    checkFinish(maze);

    for (int i = 0; i < 4; i++) {
        if (!isInFinish_
         && checkBorder(maze, i)
         && checkVisit(i)
         && canMove(maze, direction_[i])) {
            doSetWayAction(unitPosition_, 1, maze);
            doMoveUnitAction(i, true);
            backTraking(app, maze);
            if (isInFinish_) {
                returnUnit(i, false);
                doSetWayAction(unitPosition_, 3, maze);
            }
            else {
                returnUnit(i, true);
                doSetWayAction(unitPosition_, 2, maze);
            }
        }
    }
    if (!isInFinish_ && !isVisited_[unitPosition_.first][unitPosition_.second])
        doSetWayAction(unitPosition_, 2, maze);
}

void BackTraking::doSetWayAction(std::pair<int, int> pos, int value, Maze& maze) {
    setWay(pos, maze);
    addSetWayAction(pos, value);
}

void BackTraking::doMoveUnitAction(int direction, bool isPush) {
    moveUnit(direction);
    if (isPush)
        addMoveUnitAction(direction);
}

void BackTraking::returnUnit(int direction, bool isPush) {

    switch (direction) {

        case 0:
            direction = 2;
            break;
        case 1:
            direction = 3;
            break;
        case 2:
            direction = 0;
            break;
        case 3:
            direction = 1;
            break;

    }

    doMoveUnitAction(direction, isPush);
}

void BackTraking::setWay(std::pair<int, int> pos, Maze& maze) {
    isVisited_[pos.first][pos.second] = 5;
    maze.setWayCell(pos.first, pos.second, 5);
}

void BackTraking::moveUnit(int direction) {
    unitPosition_.first += iMov_[direction];
    unitPosition_.second += jMov_[direction];
}

void BackTraking::addSetWayAction(std::pair<int, int> pos, int value) {
    action_.push({"sw", value, pos.first, pos.second});
}

void BackTraking::addMoveUnitAction(int direction) {
    action_.push({"mu", direction, 0, 0});
}

bool BackTraking::checkVisit(int direction) {
    return !isVisited_[unitPosition_.first + iMov_[direction]][unitPosition_.second + jMov_[direction]];
}

bool BackTraking::checkBorder(Maze& maze, int direction) {
    return (unitPosition_.first + iMov_[direction] > -1) && (unitPosition_.first + iMov_[direction] < maze.getMazeSize())
        && (unitPosition_.second + jMov_[direction] > -1) && (unitPosition_.second + jMov_[direction] < maze.getMazeSize());
}

void BackTraking::checkFinish(Maze& maze) {
    if (unitPosition_ == maze.getFinishPosition()) {
        isInFinish_ = true;
        doSetWayAction(unitPosition_, 3, maze);
    }
}

bool BackTraking::canMove(Maze& maze, char direction) {

    switch (direction) {

        case 'l':
            return !maze.isVerticalWall(unitPosition_.first, unitPosition_.second - 1);

        case 'u':
            return !maze.isHorizontalWall(unitPosition_.first - 1, unitPosition_.second);

        case 'r':
            return !maze.isVerticalWall(unitPosition_.first, unitPosition_.second);

        case 'd':
            return !maze.isHorizontalWall(unitPosition_.first, unitPosition_.second);

    }

    return false;
}

void BackTraking::clearAction() {
    while (!action_.empty())
        action_.pop();
}

BackTraking::actionType BackTraking::getAction() {
    if (anyAction()) {
        actionType action = action_.front();
        action_.pop();
        return action;
    }
    return {"null", 0, 0, 0};
}

bool BackTraking::anyAction() {
    return !action_.empty();
}

#include "../include/Maze.h"


void Maze::printMaze(sf::RenderWindow& app) {

    sf::Font font;
    font.loadFromFile("../font/Monocraft.ttf");

    for (int i = 0; i < mazeSize_; i++) {
        for (int j = 0; j < mazeSize_; j++) {

            vertWallSprite_.setPosition(27 + j * 60 * scale_, 63 + i * 60 * scale_);
            horWallSprite_.setPosition(27 + j * 60 * scale_, 63 + i * 60 * scale_);

            switch (ways_[i][j]) {
                case 1:
                    redCell_.setPosition(27 + j * scale_ * 60, 63 + i * scale_ * 60);
                    app.draw(redCell_.getSprite());
                break;
                case 2:
                    grayCell_.setPosition(27 + j * scale_ * 60, 63 + i * scale_ * 60);
                    app.draw(grayCell_.getSprite());
                break;
                case 3:
                    greenCell_.setPosition(27 + j * scale_ * 60, 63 + i * scale_ * 60);
                    app.draw(greenCell_.getSprite());
                break;
            }

            if (horizontalWalls_[i][j] && i != mazeSize_ - 1)
                app.draw(horWallSprite_.getSprite());
            if (verticalWalls_[i][j] && j != mazeSize_ - 1)
                app.draw(vertWallSprite_.getSprite());

        }
    }

    app.draw(frameSprite_.getSprite());

    startSprite_.setPosition(27 + start_.second * 60 * scale_, 63 + start_.first * 60 * scale_);
    app.draw(startSprite_.getSprite());

    finishSprite_.setPosition(27 + finish_.second * 60 * scale_, 63 + finish_.first * 60 * scale_);
    app.draw(finishSprite_.getSprite());

}

void Maze::setStartPosition(int i, int j) {
    start_.first = i;
    start_.second = j;
}

void Maze::setFinishPosition(int i, int j) {
    finish_.first = i;
    finish_.second = j;
}

void Maze::setCellOfSet(int val, int i, int j) {
    vecOfSet_[i][j] = val;
}

void Maze::setHorizontalWall(int i, int j) {
    horizontalWalls_[i][j] = true;
}

void Maze::deleteHorizontalWall(int i, int j) {
    horizontalWalls_[i][j] = false;
}

void Maze::deleteVerticalWall(int i, int j) {
    verticalWalls_[i][j] = false;
}

void Maze::setVerticalWall(int i, int j) {
    verticalWalls_[i][j] = true;
}

void Maze::setWayCell(int i, int j, int value) {
    ways_[i][j] = value;
}

int Maze::getMazeSize() {
    return mazeSize_;
}

int Maze::getValueOfCell(int i, int j) {
    return vecOfSet_[i][j];
}

std::pair<int, int> Maze::getStartPosition() {
    return start_;
}
std::pair<int, int> Maze::getFinishPosition() {
    return finish_;
}

bool Maze::isHorizontalWall(int i, int j) {
    return horizontalWalls_[i][j];
}

bool Maze::isVerticalWall(int i, int j) {
    return verticalWalls_[i][j];
}

bool Maze::isMazeEmpty() {
    for (int i = 0; i < mazeSize_; i++)
        for (int j = 0; j < mazeSize_; j++) {
            if (vecOfSet_[i][j] ||  horizontalWalls_[i][j] || verticalWalls_[i][j])
                return 0;
        }
    return 1;
}

void Maze::setMazeSize(int mazeSize) {
    mazeSize_ = mazeSize;
    scale_ = 10 / float(mazeSize_);
    changeScale();
    initMaze();
}

void Maze::clearMaze() {
    for (int i = 0; i < mazeSize_; i++)
        for (int j = 0; j < mazeSize_; j++) {
            vecOfSet_[i][j] = 0;
            horizontalWalls_[i][j] = false;
            verticalWalls_[i][j] = false;
            ways_[i][j] = 0;
        }
}

void Maze::clearWays() {
    for (int i = 0; i < mazeSize_; i++)
        for (int j = 0; j < mazeSize_; j++)
            ways_[i][j] = 0;
}

void Maze::initMaze() {

    vecOfSet_ = std::vector<std::vector<int>> (mazeSize_, std::vector<int> (mazeSize_, EMPTY_CELL));
    ways_ = vecOfSet_;

    std::vector<std::vector<bool>> sample(mazeSize_, std::vector<bool> (mazeSize_, EMPTY_CELL));
    verticalWalls_ = sample;
    horizontalWalls_ = sample;

    start_.first = 0; start_.second = 0;
    finish_.first = mazeSize_ - 1; finish_.second = mazeSize_ - 1;
}

void Maze::changeScale() {
    vertWallSprite_.setScale(scale_);
    horWallSprite_.setScale(scale_);
    startSprite_.setScale(scale_);
    finishSprite_.setScale(scale_);
    grayCell_.setScale(scale_);
    redCell_.setScale(scale_);
    greenCell_.setScale(scale_);
}

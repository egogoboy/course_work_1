#include "BackTracking.h"

BackTracking::backTraking() {

}

BackTracking::startBackTracking() {
    unitPosition_ = Maze.getStartPosition();
    backTraking();
}

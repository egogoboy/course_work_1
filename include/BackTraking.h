#ifndef BACKTRAKING_H
#define BACKTRAKING_H
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Maze.h>
#include <MySprite.h>
#include <Button.h>
#include <queue>

class BackTraking {

    protected:

        static inline int iMov_[4] = { 0,   -1,  0,   1};
        static inline int jMov_[4] = {-1,   0,   1,   0};

        struct actionType {
            std::string name;
            int value, x, y;
        };

    public:

        static void startBackTraking(sf::RenderWindow& app, Maze& maze);
        static bool anyAction();
        static BackTraking::actionType getAction();

    private:

        static void backTraking(sf::RenderWindow& app, Maze& maze);
        static bool canMove(Maze& maze, char direction);
        static void checkFinish(Maze& maze);
        static bool checkBorder(Maze& maze, int direction);
        static bool checkVisit(int direction);
        static void clearAction();
        static void doMoveUnitAction(int direction, bool isPush);
        static void returnUnit(int direction, bool isPush);
        static void moveUnit(int direction);
        static void addMoveUnitAction(int direction);
        static void doSetWayAction(std::pair<int, int> pos, int value, Maze& maze);
        static void setWay(std::pair<int, int> pos, Maze& maze);
        static void addSetWayAction(std::pair<int, int> pos, int value);

        static inline bool isInFinish_;
        static inline std::vector<std::vector<int>> isVisited_;
        static inline std::pair<int, int> unitPosition_;
        static inline std::queue<actionType> action_;
        static inline char direction_[4] = {'l', 'u', 'r', 'd'};

        static inline Button pauseButton_;

        static inline sf::Text pauseText_;

};

#endif // BACKTRACKING_H

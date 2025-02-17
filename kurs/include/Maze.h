#include <vector>
#include <SFML/Graphics.hpp>
#include <MySprite.h>
#ifndef MAZE_H
#define MAZE_H

class Maze {
    public:

        Maze(int mazeSize) : mazeSize_(mazeSize) {
            initMaze();

            vertWallSprite_.setTexture("images/vertical_right_line.png");
            horWallSprite_.setTexture("images/horizontal_low_line.png");
            frameSprite_.setTexture("images/frame.png");
            frameSprite_.setPosition(20, 56);
            startSprite_.setTexture("images/start.png");
            finishSprite_.setTexture("images/finish.png");
            grayCell_.setTexture("images/gray_track_cell.png");
            redCell_.setTexture("images/red_track_cell.png");
            greenCell_.setTexture("images/green_track_cell.png");

        }

        void initMaze();

        bool isHorizontalWall(int i, int j);
        bool isVerticalWall(int i, int j);
        int getValueOfCell(int i, int j);
        int getMazeSize();

        void setCellOfSet(int value, int i, int j);
        void setHorizontalWall(int i, int j);
        void setVerticalWall(int i, int j);
        void setMazeSize(int mazeSize);
        void setWayCell(int i, int j, int value);
        void setStartPosition(int i, int j);
        void setFinishPosition(int i, int j);

        void deleteHorizontalWall(int i, int j);
        void deleteVerticalWall(int i, int j);
        void clearMaze();
        void clearWays();
        std::pair<int, int> getStartPosition();
        std::pair<int, int> getFinishPosition();

        void printMaze(sf::RenderWindow& app);
        bool isMazeEmpty();

    protected:
        float scale_ = 1;

    private:

        void changeScale();

        int mazeSize_;

        std::pair<int, int> start_,
                            finish_;

        std::vector<std::vector<int>> vecOfSet_;
        std::vector<std::vector<bool>> verticalWalls_;
        std::vector<std::vector<bool>> horizontalWalls_;
        std::vector<std::vector<int>> ways_;

        MySprite vertWallSprite_,
                 horWallSprite_,
                 frameSprite_,
                 startSprite_,
                 finishSprite_,
                 grayCell_,
                 redCell_,
                 greenCell_;

        const int PIXEL_MAZE_SIZE{640};
        const int EMPTY_CELL{0};
        //const string MAZE_CREATED = "log: maze was created\n";
        //const string MAZE_CLEARED = "log: maze was cleared\n";
};

#endif

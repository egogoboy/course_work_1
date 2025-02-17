#ifndef UserInterface_H
#define UserInterface_H
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Button.h>
#include <Maze.h>
#include <MazeGeneration.h>
#include <BackTraking.h>
#include <MySprite.h>

class UserInterface : protected BackTraking, protected Maze {
    public:
        UserInterface(Maze& maze): Maze(10) {

            font_.loadFromFile("font/Monocraft.ttf");
            scale_ = 1;
            countOfReturns_ = 0;

            setlocale(LC_ALL, "Russian");
            isDrawBackTracking_ = false;

            initText(genText_, "новый лабиринт", 716, 74);
            initText(searchText_, "начать поиск", 1040, 74);
            initText(incMazeSizeText_, "+", 682, 185);
            initText(decMazeSizeText_, "-", 682, 286);
            initText(defaultSizeText_, "сбросить размер", 747, 185);
            initText(mazeSizeText_, std::to_string(maze.getMazeSize()), 676, 236);
            initText(changeMazeSizeText_, "размер поля", 764, 236);
            initText(changeSearchFramerateText_, "скорость поиска", 1058, 236);
            initText(incSearchFramerate_, "+", 994, 185);
            initText(decSearchFramerate_, "-", 994, 286);
            initText(defaultFramerateText_, "сброс скорости", 1064, 185);
            initText(searchFramerateText_, "90%", 982, 236);
            initText(backTrackingPauseText_, "остановить поиск", 1020, 394);
            initText(backTrackingDrawNextStepText_, "следующий шаг", 1033, 495);
            initText(closeProgramText_, "x", 1243, 12);
            closeProgramText_.setCharacterSize(25);
            initText(headerText_, "поиск выхода из лабиринта методом бэктрэкинга", 65, 20);
            initText(userEditPositionText_, "", 667, 595);
            initText(clearMazeText_, "очистить лабиринт", 701, 395);
            initText(countOfReturnsText_, "количество возвратов: " + std::to_string(countOfReturns_), 27, 670);
            initText(isFoundFinish_, "", 400, 670);
            initText(editMazeManualText_,
                     "старт - зёленый квадрат\nфиниш - оранжевый квадрат\n\nнажмите на старт/финиш для его редактирования,\nследующим нажатием установите новую позицию\n\nредактирование границ:\n  создать - удерживайте ЛКМ и проведите между клетками\n  удалить - удерживайте ПКМ и проведите между клетками", 660, 70);

            initText(manualButtonText_, "справка", 749, 495);
            generateButton_.setAllOptions(667, 63, 255, 45);
            startSearch_.setAllOptions(979, 63, 255, 45);
            incMazeSizeButton_.setAllOptions(667, 175, 40, 40);
            decMazeSizeButton_.setAllOptions(667, 276, 40, 40);
            resetToDefaultMazeSizeButton_.setAllOptions(734, 175, 188, 40);
            incSearchFramerateButton_.setAllOptions(979, 175, 40, 40);
            decSearchFramerateButton_.setAllOptions(979, 276, 40, 40);
            resetToDefaultSearchFramerateButton_.setAllOptions(1046, 175, 188, 40);
            drawBackTrackingSearchPauseButton_.setAllOptions(979, 383, 255, 45);
            nextStepButton_.setAllOptions(979, 484, 255, 45);
            closeProgramButton_.setAllOptions(1235, 14, 30, 30);
            closeProgramButton_.setBorderSize(3);
            closeProgramButton_.setColor(sf::Color(255, 25, 0));
            clearMazeButton_.setAllOptions(667, 383, 255, 45);
            manualButton_.setAllOptions(667, 484, 255, 45);

            editStartPosButton_.setPosition(27 + maze.getStartPosition().first * 60, 63 + maze.getStartPosition().second * 60);
            editStartPosButton_.setSize(60 * scale_, 60 * scale_);

            editFinishPosButton_.setPosition(27 + maze.getFinishPosition().first * 60, 63 + maze.getFinishPosition().second * 60);
            editFinishPosButton_.setSize(60 * scale_, 60 * scale_);

            unitSprite_.setTexture("images/unit.png");
            drawBackTrackingPause_ = false;
            canDrawNextStep_ = true;
            backTrackingDrawCooldownBoost_ = defaultBackTrackingDrawCooldownBoost_;

            currentMousePosAtMaze_ = {0, 0};

            setStartPositionCooldown_ = 10;
            setFinishPositionCooldown_ = 10;
            userEditPositionTextPulseCooldown_ = 100;
            isEditPositionTextVisible_ = true;
            userChangeStartPosition_ = false;
            userChangeFinishPosition_ = false;
            isDrawManual_ = false;

        }

        void drawUserInterface(sf::RenderWindow& app, Maze& maze);
        void updateUserInterface(sf::RenderWindow& app, Maze& maze);

        void initText(sf::Text& text, std::string s, float xPos, float yPos);

    protected:

    private:

        void mazeSizeChanging(sf::RenderWindow& app, Maze& maze);
        void searchFramerateChanging(sf::RenderWindow& app);
        void printBackTracking(sf::RenderWindow& app, Maze& maze);
        void processStep(actionType step, Maze& maze);
        void moveBackTrackingUnit(actionType step);
        void setCorrectWay(actionType step, Maze& maze);
        void drawAllButton(sf::RenderWindow& app, Maze& maze);
        void drawAllText(sf::RenderWindow& app, Maze& maze);
        void updatePauseText();
        int charToInt(char c);
        void editMaze(sf::RenderWindow& app, Maze& maze);
        bool mouseInFrame(sf::RenderWindow& app);

        sf::Font font_;
        Button generateButton_,
               incMazeSizeButton_,
               decMazeSizeButton_,
               startSearch_,
               resetToDefaultMazeSizeButton_,
               incSearchFramerateButton_,
               decSearchFramerateButton_,
               resetToDefaultSearchFramerateButton_,
               drawBackTrackingSearchPauseButton_,
               nextStepButton_,
               closeProgramButton_,
               clearMazeButton_,
               editStartPosButton_,
               editFinishPosButton_,
               manualButton_;

        sf::Text mazeSizeText_;

        sf::Text searchText_,
                 incMazeSizeText_,
                 decMazeSizeText_,
                 genText_,
                 defaultSizeText_,
                 changeMazeSizeText_,
                 changeSearchFramerateText_,
                 incSearchFramerate_,
                 decSearchFramerate_,
                 defaultFramerateText_,
                 searchFramerateText_,
                 backTrackingPauseText_,
                 backTrackingDrawNextStepText_,
                 closeProgramText_,
                 headerText_,
                 userEditPositionText_,
                 clearMazeText_,
                 editMazeManualText_,
                 manualButtonText_,
                 countOfReturnsText_,
                 isFoundFinish_;

        MySprite unitSprite_;
        int unitXPos_,
            unitYPos_,
            backTrackingDrawCooldownBoost_,
            backTrackingDrawCooldown_,
            setStartPositionCooldown_,
            setFinishPositionCooldown_,
            userEditPositionTextPulseCooldown_,
            countOfReturns_;

        float scale_;

        const int defaultMazeSize_ = 10,
                  defaultBackTrackingDrawCooldownBoost_ = 90,
                  cooldownValue_ = 100;

        bool isDrawBackTracking_,
             drawBackTrackingPause_,
             canDrawNextStep_,
             userChangeStartPosition_,
             userChangeFinishPosition_,
             isEditPositionTextVisible_,
             isDrawManual_;

        std::pair<int, int> currentMousePosAtMaze_;
};

#endif

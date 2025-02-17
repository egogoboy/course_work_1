#include "Interface.h"

void UserInterface::drawUserInterface(sf::RenderWindow& app, Maze& maze) {

    drawAllButton(app, maze);
    if (!isDrawManual_) {
        updatePauseText();
    }
    drawAllText(app, maze);

    maze.printMaze(app);
    if (!isDrawManual_) {

        if (isDrawBackTracking_) {
           printBackTracking(app, maze);
        }
    }

}

void UserInterface::updateUserInterface(sf::RenderWindow& app, Maze& maze) {
    sf::Event event;

    while (app.pollEvent(event)) {
        if ((event.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || closeProgramButton_.isPressed(app)))
            app.close();
    }

    if (!isDrawManual_) {

        if (userEditPositionTextPulseCooldown_ != 0) {
            userEditPositionTextPulseCooldown_--;
        }
        else {
            userEditPositionTextPulseCooldown_ = 200;
        }

        if (!isDrawBackTracking_)
            editMaze(app, maze);

        if (generateButton_.isPressed(app) || sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            MazeGeneration::generateMaze(maze, app);
            isDrawBackTracking_ = false;
            userChangeFinishPosition_ = false;
            userChangeStartPosition_ = false;
            countOfReturns_ = 0;
            userEditPositionText_.setString("");
            editStartPosButton_.setPosition(27 + maze.getStartPosition().second * 60 * scale_, 63 + maze.getStartPosition().first * 60 * scale_);
            editFinishPosButton_.setPosition(27 + maze.getFinishPosition().second * 60 * scale_, 63 + maze.getFinishPosition().first * 60 * scale_);
            isFoundFinish_.setString("");
        }

        if (startSearch_.isPressed(app) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            maze.clearWays();
            countOfReturns_ = 0;
            backTrackingDrawCooldown_ = 0;
            drawBackTrackingPause_ = false;
            BackTraking::startBackTraking(app, maze);
            unitXPos_ = maze.getStartPosition().second;
            unitYPos_ = maze.getStartPosition().first;
            unitSprite_.setPosition(27 + unitXPos_ * scale_ * 60, 63 + unitYPos_ * scale_ * 60);
            isDrawBackTracking_ = true;
            userEditPositionText_.setString("");
            isFoundFinish_.setString("выход не найден");
            isFoundFinish_.setFillColor(sf::Color::Red);
        }

        if (drawBackTrackingSearchPauseButton_.isPressed(app))
            drawBackTrackingPause_ = !drawBackTrackingPause_;

        canDrawNextStep_ = !drawBackTrackingPause_;

        if (nextStepButton_.isPressed(app)) {
            canDrawNextStep_ = true;
            backTrackingDrawCooldown_ = 0;
        }

        if (editStartPosButton_.isPressed(app) && !setStartPositionCooldown_ && !userChangeFinishPosition_) {
            userChangeStartPosition_ = !userChangeStartPosition_;
            userEditPositionTextPulseCooldown_ = 200;
            isEditPositionTextVisible_ = true;
            userEditPositionText_.setFillColor(sf::Color(0, 0, 0, 1000 * isEditPositionTextVisible_));
            userEditPositionText_.setString("вы редактируете старт");
        }

        if (editFinishPosButton_.isPressed(app) && !setFinishPositionCooldown_ && !userChangeStartPosition_) {
            userChangeFinishPosition_ = !userChangeFinishPosition_;
            userEditPositionTextPulseCooldown_ = 200;
            isEditPositionTextVisible_ = true;
            userEditPositionText_.setFillColor(sf::Color(0, 0, 0, 1000 * isEditPositionTextVisible_));
            userEditPositionText_.setString("вы редактируете финиш");
        }

        if (clearMazeButton_.isPressed(app)) {
            maze.clearMaze();
            countOfReturns_ = 0;
            isDrawBackTracking_ = false;
            isFoundFinish_.setString("");
        }

        if (editFinishPosButton_.isPressed(app))
            userChangeFinishPosition_ = !userChangeFinishPosition_;

        mazeSizeChanging(app, maze);
        searchFramerateChanging(app);
    }

    if (manualButton_.isPressed(app))
        isDrawManual_ = !isDrawManual_;

}

void UserInterface::printBackTracking(sf::RenderWindow& app, Maze& maze) {

    if (backTrackingDrawCooldown_ - backTrackingDrawCooldownBoost_ <= 0) {
        backTrackingDrawCooldown_ = cooldownValue_;

        if (BackTraking::anyAction() && canDrawNextStep_) {
            actionType step = BackTraking::getAction();

            processStep(step, maze);

        }
    }
    else {
        backTrackingDrawCooldown_--;
    }

    app.draw(unitSprite_.getSprite());

    if (!BackTraking::anyAction())
        isDrawBackTracking_ = false;
}

void UserInterface::editMaze(sf::RenderWindow& app, Maze& maze) {
    if (mouseInFrame(app)) {

        std::pair<int, int> oldMousePosAtMaze = currentMousePosAtMaze_;
        currentMousePosAtMaze_.first = (sf::Mouse::getPosition(app).y - 63) / (60 * scale_);
        currentMousePosAtMaze_.second = (sf::Mouse::getPosition(app).x - 27) / (60 * scale_);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (std::abs(oldMousePosAtMaze.first - currentMousePosAtMaze_.first + oldMousePosAtMaze.second - currentMousePosAtMaze_.second) == 1) {
                    if (oldMousePosAtMaze.first != currentMousePosAtMaze_.first) {
                        maze.setHorizontalWall(std::min(oldMousePosAtMaze.first, currentMousePosAtMaze_.first), std::min(oldMousePosAtMaze.second, currentMousePosAtMaze_.second));
                        isFoundFinish_.setString("");
                    }
                    else {
                        maze.setVerticalWall(std::min(oldMousePosAtMaze.first, currentMousePosAtMaze_.first), std::min(oldMousePosAtMaze.second, currentMousePosAtMaze_.second));
                        isFoundFinish_.setString("");
                    }
                }
                if (userChangeStartPosition_){
                    if (maze.getFinishPosition() != currentMousePosAtMaze_ && maze.getStartPosition() != currentMousePosAtMaze_) {
                        maze.setStartPosition(currentMousePosAtMaze_.first, currentMousePosAtMaze_.second);
                        editStartPosButton_.setPosition(27 + maze.getStartPosition().second * 60 * scale_, 63 + maze.getStartPosition().first * 60 * scale_);
                        userChangeStartPosition_ = false;
                        setStartPositionCooldown_ = 200;
                        userEditPositionText_.setString("");
                        isFoundFinish_.setString("");
                    }
                }

                if (userChangeFinishPosition_) {
                    if (maze.getFinishPosition() != currentMousePosAtMaze_ && maze.getStartPosition() != currentMousePosAtMaze_) {
                        maze.setFinishPosition(currentMousePosAtMaze_.first, currentMousePosAtMaze_.second);
                        editFinishPosButton_.setPosition(27 + maze.getFinishPosition().second * 60 * scale_, 63 + maze.getFinishPosition().first * 60 * scale_);
                        userChangeFinishPosition_ = false;
                        setFinishPositionCooldown_ = 200;
                        userEditPositionText_.setString("");
                        isFoundFinish_.setString("");
                    }
                }
            }
            else {
                if (setStartPositionCooldown_ != 0)
                    setStartPositionCooldown_--;
                if (setFinishPositionCooldown_ != 0)
                    setFinishPositionCooldown_--;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (std::abs(oldMousePosAtMaze.first - currentMousePosAtMaze_.first + oldMousePosAtMaze.second - currentMousePosAtMaze_.second) == 1) {
                    if (oldMousePosAtMaze.first != currentMousePosAtMaze_.first) {
                        maze.deleteHorizontalWall(std::min(oldMousePosAtMaze.first, currentMousePosAtMaze_.first), std::min(oldMousePosAtMaze.second, currentMousePosAtMaze_.second));
                        isFoundFinish_.setString("");
                    }
                    else {
                        maze.deleteVerticalWall(std::min(oldMousePosAtMaze.first, currentMousePosAtMaze_.first), std::min(oldMousePosAtMaze.second, currentMousePosAtMaze_.second));
                        isFoundFinish_.setString("");
                    }
                }
            }
        }
    }

void UserInterface::processStep(actionType step, Maze& maze) {
    if (step.name == "sw") {
        maze.setWayCell(step.x, step.y, step.value);
        if (step.value == 2)
            countOfReturns_++;

        if (step.value == 3) {
            isDrawBackTracking_ = false;
            setCorrectWay(step, maze);
            isFoundFinish_.setString("выход найден");
            isFoundFinish_.setFillColor(sf::Color::Green);
        }

    }

    if (step.name == "mu")
        moveBackTrackingUnit(step);
}

void UserInterface::setCorrectWay(actionType step, Maze& maze) {
    while (BackTraking::anyAction()) {
        step = BackTraking::getAction();
        maze.setWayCell(step.x, step.y, step.value);
    }
}

void UserInterface::moveBackTrackingUnit(actionType step) {
    unitXPos_ += jMov_[step.value];
    unitYPos_ += iMov_[step.value];
    unitSprite_.setPosition(27 + unitXPos_ * scale_ * 60, 63 + unitYPos_ * scale_ * 60);
}

void UserInterface::mazeSizeChanging(sf::RenderWindow& app, Maze& maze) {
    if (incMazeSizeButton_.isPressed(app) && maze.getMazeSize() < 30) {
        maze.setMazeSize(maze.getMazeSize() + 1);
        isDrawBackTracking_ = false;
        scale_ = 10 / float(maze.getMazeSize());
        unitSprite_.setScale(scale_);
        editStartPosButton_.setSize(60 * scale_, 60 * scale_);
        editStartPosButton_.setPosition(27 + maze.getStartPosition().first * 60 * scale_, 63 + maze.getStartPosition().second * 60 * scale_);
        editFinishPosButton_.setSize(60 * scale_, 60 * scale_);
        editFinishPosButton_.setPosition(27 + maze.getFinishPosition().first * 60 * scale_, 63 + maze.getFinishPosition().second * 60 * scale_);
        mazeSizeText_.setString(std::to_string(maze.getMazeSize()));
        isFoundFinish_.setString("");
        countOfReturns_ = 0;
    }

    if (decMazeSizeButton_.isPressed(app) && maze.getMazeSize() > 3) {
        maze.setMazeSize(maze.getMazeSize() - 1);
        isDrawBackTracking_ = false;
        scale_ = 10 / float(maze.getMazeSize());
        unitSprite_.setScale(scale_);
        editStartPosButton_.setSize(60 * scale_, 60 * scale_);
        editStartPosButton_.setPosition(27 + maze.getStartPosition().first * 60 * scale_, 63 + maze.getStartPosition().second * 60 * scale_);
        editFinishPosButton_.setSize(60 * scale_, 60 * scale_);
        editFinishPosButton_.setPosition(27 + maze.getFinishPosition().first * 60 * scale_, 63 + maze.getFinishPosition().second * 60 * scale_);
        mazeSizeText_.setString(std::to_string(maze.getMazeSize()));
        isFoundFinish_.setString("");
        countOfReturns_ = 0;
    }

    if (maze.getMazeSize() != defaultMazeSize_ && resetToDefaultMazeSizeButton_.isPressed(app)) {
        maze.setMazeSize(defaultMazeSize_);
        isDrawBackTracking_ = false;
        scale_ = 10 / float(maze.getMazeSize());
        unitSprite_.setScale(scale_);
        editStartPosButton_.setSize(60 * scale_, 60 * scale_);
        editStartPosButton_.setPosition(27 + maze.getStartPosition().first * 60 * scale_, 63 + maze.getStartPosition().second * 60 * scale_);
        editFinishPosButton_.setSize(60 * scale_, 60 * scale_);
        editFinishPosButton_.setPosition(27 + maze.getFinishPosition().first * 60 * scale_, 63 + maze.getFinishPosition().second * 60 * scale_);
        mazeSizeText_.setString(std::to_string(defaultMazeSize_));
        isFoundFinish_.setString("");
        countOfReturns_ = 0;
    }
}

void UserInterface::searchFramerateChanging(sf::RenderWindow& app) {
    if (incSearchFramerateButton_.isPressed(app) && backTrackingDrawCooldownBoost_ < 100) {
        backTrackingDrawCooldownBoost_ += 10;
        searchFramerateText_.setString(std::to_string(backTrackingDrawCooldownBoost_) + "%");
    }

    if (decSearchFramerateButton_.isPressed(app) && backTrackingDrawCooldownBoost_ > 10) {
        backTrackingDrawCooldownBoost_ -= 10;
        searchFramerateText_.setString(std::to_string(backTrackingDrawCooldownBoost_) + "%");
    }

    if (backTrackingDrawCooldownBoost_ != defaultBackTrackingDrawCooldownBoost_ && resetToDefaultSearchFramerateButton_.isPressed(app)) {
        backTrackingDrawCooldownBoost_ = defaultBackTrackingDrawCooldownBoost_;
        searchFramerateText_.setString(std::to_string(backTrackingDrawCooldownBoost_) + "%");
    }
}

void UserInterface::initText(sf::Text& text, std::string s, float xPos, float yPos) {
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Black);
    text.setFont(font_);
    text.setString(s);
    text.setPosition(xPos, yPos);
}

void UserInterface::updatePauseText() {
    if (drawBackTrackingPause_) {
        backTrackingPauseText_.setString("продолжить поиск");
     }
     else {
        backTrackingPauseText_.setString("остановить поиск");
     }
}

int UserInterface::charToInt(char c) {
    return int(c - '0');
}

bool UserInterface::mouseInFrame(sf::RenderWindow& app) {
    return (sf::Mouse::getPosition(app).x >= 27 && sf::Mouse::getPosition(app).x <= 627
    &&  sf::Mouse::getPosition(app).y >= 63 && sf::Mouse::getPosition(app).y <= 663);
}

void UserInterface::drawAllButton(sf::RenderWindow& app, Maze& maze) {

    manualButton_.drawButton(app);
    closeProgramButton_.drawButton(app);
    if (!isDrawManual_) {
        generateButton_.drawButton(app);
        startSearch_.drawButton(app);
        incMazeSizeButton_.drawButton(app);
        decMazeSizeButton_.drawButton(app);
        incSearchFramerateButton_.drawButton(app);
        decSearchFramerateButton_.drawButton(app);
        drawBackTrackingSearchPauseButton_.drawButton(app);
        nextStepButton_.drawButton(app);
        editStartPosButton_.drawButton(app);
        editFinishPosButton_.drawButton(app);

        if (!maze.isMazeEmpty())
            clearMazeButton_.drawButton(app);

        if (maze.getMazeSize() != defaultMazeSize_)
            resetToDefaultMazeSizeButton_.drawButton(app);

        if (backTrackingDrawCooldownBoost_ != defaultBackTrackingDrawCooldownBoost_)
            resetToDefaultSearchFramerateButton_.drawButton(app);
    }

}

void UserInterface::drawAllText(sf::RenderWindow& app, Maze& maze) {

    app.draw(headerText_);
    app.draw(manualButtonText_);
    app.draw(closeProgramText_);
    app.draw(countOfReturnsText_);
        if (!isDrawBackTracking_)
            app.draw(isFoundFinish_);

    if (!isDrawManual_) {
        manualButtonText_.setString("справка");
        countOfReturnsText_.setString("количество возвратов: " + std::to_string(countOfReturns_));
        app.draw(changeMazeSizeText_);
        app.draw(changeSearchFramerateText_);
        app.draw(mazeSizeText_);
        app.draw(genText_);
        app.draw(searchText_);
        app.draw(incMazeSizeText_);
        app.draw(decMazeSizeText_);
        app.draw(incSearchFramerate_);
        app.draw(decSearchFramerate_);
        app.draw(searchFramerateText_);
        app.draw(backTrackingDrawNextStepText_);
        app.draw(backTrackingPauseText_);

        app.draw(userEditPositionText_);

        if (!maze.isMazeEmpty())
            app.draw(clearMazeText_);

        if (maze.getMazeSize() != defaultMazeSize_)
           app.draw(defaultSizeText_);

        if (backTrackingDrawCooldownBoost_ != defaultBackTrackingDrawCooldownBoost_)
           app.draw(defaultFramerateText_);

        if (userEditPositionTextPulseCooldown_ == 0) {
           isEditPositionTextVisible_ = !isEditPositionTextVisible_;
           userEditPositionText_.setFillColor(sf::Color(0, 0, 0, 1000 * isEditPositionTextVisible_));
        }

    }
    else {
        manualButtonText_.setString("закрыть");
        app.draw(editMazeManualText_);
    }

}



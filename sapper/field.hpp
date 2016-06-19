#pragma once

#include <iostream>

using namespace std;

class Field {
public:
    Field() {
        bombsAroundCount = 0;
        isBare = false;
        isArmed = false;
        isMarked = false;
    }

    size_t getBombsAroundCount() { return bombsAroundCount; }

    bool getIsBare() { return isBare; }

    bool getIsArmed() { return isArmed; }

    bool getIsMarked() { return isMarked; }

    void setBombsAroundCount(size_t _bombsAroundCount) { bombsAroundCount = _bombsAroundCount; }

    void setBare() { isBare = true; }

    void setArmed() { isArmed = true; }

    void flipMarked() { isMarked = !isMarked; }

private:
    size_t bombsAroundCount;
    bool isBare;
    bool isArmed;
    bool isMarked;
};

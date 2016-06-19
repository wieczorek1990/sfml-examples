#pragma once

#include <ctime>
#include <vector>

#include "field.hpp"

using namespace std;

enum DisarmResult {
    EMPTY, BARE, EXPLODED
};

enum MarkResult {
    MARKED, UNMARKED, ALL_MARKED
};

class Board {
public:
    Board(size_t width, size_t height, size_t bombsCount);

    MarkResult mark(size_t x, size_t y);

    DisarmResult disarm(size_t x, size_t y);

    size_t getBombsAroundCount(size_t x, size_t y) { return fields[x][y].getBombsAroundCount(); }

    bool getIsBare(size_t x, size_t y) { return fields[x][y].getIsBare(); }

private:
    void setBombs();

    void setValues();

    vector<vector<Field> > fields;
    size_t bombsCount;
    size_t width, height;
    size_t bombsFoundCount;
    size_t fieldsMarkedCount;

    void bareFloodFill(int x, int y);
};

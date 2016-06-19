#include "board.hpp"

Board::Board(size_t _width, size_t _height, size_t _bombsCount) {
    width = _width;
    height = _height;
    bombsCount = _bombsCount;

    fields.resize(width);
    for (size_t i = 0; i < width; i++) {
        fields[i].resize(height);
        for (size_t j = 0; j < height; j++) {
            fields[i][j] = Field();
        }
    }

    setBombs();
    setValues();
}

void Board::setBombs() {
    size_t bombsSet = 0;
    srand(static_cast<unsigned int>(time(nullptr)));
    while (bombsSet != bombsCount) {
        size_t x = rand() % width;
        size_t y = rand() % height;
        if (!fields[x][y].getIsArmed()) {
            fields[x][y].setArmed();
            bombsSet += 1;
        }
    }
}

void Board::setValues() {
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            size_t value = 0;
            for (short k = -1; k < 2; k++) {
                for (short l = -1; l < 2; l++) {
                    size_t x = i + k;
                    size_t y = j + l;
                    if (x < 0 || x > width - 1 || y < 0 || y > height - 1) {
                        continue;
                    }
                    if (fields[x][y].getIsArmed()) {
                        value += 1;
                    }
                }
            }
            fields[i][j].setBombsAroundCount(value);
        }
    }
}

DisarmResult Board::disarm(size_t x, size_t y) {
    Field &field = fields[x][y];
    if (field.getIsArmed()) {
        return EXPLODED;
    } else {
        if (field.getBombsAroundCount() == 0) {
            bareFloodFill(static_cast<int>(x), static_cast<int>(y));
            return BARE;
        } else {
            return EMPTY;
        }
    }
}

MarkResult Board::mark(size_t x, size_t y) {
    Field &field = fields[x][y];
    field.flipMarked();
    if (field.getIsMarked()) {
        fieldsMarkedCount += 1;
        if (field.getIsArmed()) {
            bombsFoundCount += 1;
        }
    } else {
        fieldsMarkedCount -= 1;
        if (field.getIsArmed()) {
            bombsFoundCount -= 1;
        }
    }
    if (bombsCount == bombsFoundCount && bombsCount == fieldsMarkedCount) {
        return ALL_MARKED;
    } else {
        if (field.getIsMarked()) {
            return MARKED;
        } else {
            return UNMARKED;
        }
    }
}

void Board::bareFloodFill(int x, int y) {
    if (x < 0 || x > width - 1 || y < 0 || y > height - 1) {
        return;
    }
    Field &field = fields[x][y];
    if (field.getIsBare() || field.getBombsAroundCount() != 0) {
        return;
    }
    field.setBare();
    bareFloodFill(x, y - 1);
    bareFloodFill(x + 1, y);
    bareFloodFill(x, y + 1);
    bareFloodFill(x - 1, y);
}

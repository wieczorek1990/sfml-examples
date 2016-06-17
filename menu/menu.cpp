#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "menu.hpp"

using namespace sf;
using namespace std;

Menu::Menu(float width, float height, vector<String> itemNames, int id) {
    itemCount = static_cast<int>(itemNames.size());
    selected = 0;
    identifier = id;

    if (itemCount > MAX_NUMBER_OF_ITEMS) {
        abort();
    }
    if (!font.loadFromFile("font.ttf")) {
        abort();
    }

    for (int index = 0; index < itemCount; index++) {
        Text &item = items[index];
        Color color = Color::White;
        if (index == selected) {
            color = Color::Yellow;
        }

        item.setFont(font);
        item.setColor(color);
        item.setString(itemNames[static_cast<unsigned long>(index)]);
        Rect<float> bounds = item.getLocalBounds();
        float halfTextWidth = bounds.width / 2;
        float halfTextHeight = bounds.height / 2;
        item.setPosition(width / 2 - halfTextWidth,
                         (height / (itemCount + 1)) * (index + 1) - halfTextHeight);
    }
}

void Menu::draw(RenderWindow &window) {
    for (int i = 0; i < itemCount; i++) {
        window.draw(items[i]);
    }
}

void Menu::move(bool up) {
    short step;
    if (up) {
        step = -1;
    } else {
        step = 1;
    }
    int old = selected;
    selected = (old + step) % itemCount;
    if (selected < 0) {
        selected = itemCount - 1;
    }

    items[old].setColor(Color::White);
    items[selected].setColor(Color::Yellow);
}

void Menu::up() {
    move(true);
}

void Menu::down() {
    move(false);
}

int Menu::choose() {
    return selected;
}

int Menu::getId() {
    return identifier;
}


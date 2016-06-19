#pragma once

#ifdef _WIN32

#include <SFML\Graphics.hpp>

#else

#include <SFML/Graphics.hpp>

#endif

class Game {
public:
    int run(size_t difficulty);

    bool contains(sf::RectangleShape &shape, sf::Vector2<float> position,
                  size_t fieldSize, size_t i, size_t j, float outlineSize);

    void setupText(sf::Text &text, sf::Font &font, sf::Color &color);

    sf::Vector2<float> getTextAdjustment(sf::Text &text);

    void centerText(sf::Window &window, sf::Text &text, sf::Font &font, sf::Color &color, sf::String string);
};

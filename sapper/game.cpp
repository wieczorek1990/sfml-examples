#include "game.hpp"
#include "field.hpp"
#include "board.hpp"
#include "constants.hpp"

using namespace sf;
using namespace std;

bool Game::contains(RectangleShape &shape, Vector2<float> position,
                    size_t fieldSize, size_t i, size_t j, float outlineSize) {
    Vector2<float> bounds = shape.getSize();
    size_t x = fieldSize * i;
    size_t y = fieldSize * j;
    size_t outline = static_cast<size_t>(outlineSize);
    return position.x > x + outline && position.x < x + bounds.x - outline &&
           position.y > y + outline && position.y < y + bounds.y - outline;
}

void Game::setupText(Text &text, Font &font, Color &color) {
    text.setFont(font);
    text.setColor(color);
}

Vector2<float> Game::getTextAdjustment(Text &text) {
    Rect<float> bounds = text.getLocalBounds();
    return Vector2<float>(bounds.width / 2, bounds.height / 2);
}

void Game::centerText(Window &window, Text &text, Font &font, Color &color, String string) {
    setupText(text, font, color);
    text.setString(string);
    Vector2<float> adjustment = getTextAdjustment(text);
    float halfWindowWidth = window.getSize().x / 2.0f;
    float halfWindowHeight = window.getSize().y / 2.0f;
    float x = halfWindowWidth - adjustment.x;
    float y = halfWindowHeight - adjustment.y;
    text.setPosition(x, y);
}

int Game::run(size_t difficulty) {
    RectangleShape fieldViews[Constants::MAX_BOARD_SIZE][Constants::MAX_BOARD_SIZE];
    Text numbersView[Constants::MAX_BOARD_SIZE][Constants::MAX_BOARD_SIZE];
    sf::RenderWindow window(sf::VideoMode(Constants::WINDOW_SIZE, Constants::WINDOW_SIZE), "Sapper");
    Color colorGrey = Color(128, 128, 128);
    Color colorDarkGrey = Color(64, 64, 64);
    float outlineSize = 8.0f;
    size_t size = 6 + difficulty * 3;
    size_t bombsCount = static_cast<size_t>(size * size * Constants::BOMB_PERCENTAGE);
    Board board(size, size, bombsCount);
    size_t fieldSize = Constants::WINDOW_SIZE / size;
    Color color = Color::Yellow;

    sf::Text message;
    sf::Font font;

    font.loadFromFile("font.ttf");
    centerText(window, message, font, color, "END");

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            float x, y;

            x = i * Constants::WINDOW_SIZE / size;
            y = j * Constants::WINDOW_SIZE / size;
            RectangleShape &fieldView = fieldViews[i][j];
            fieldView.setPosition(x, y);
            fieldView.setSize(Vector2<float>(fieldSize, fieldSize));
            fieldView.setFillColor(colorDarkGrey);
            fieldView.setOutlineColor(Color::Black);
            fieldView.setOutlineThickness(outlineSize);

            Text &numberView = numbersView[i][j];
            setupText(numberView, font, color);
        }
    }

    bool quit = false;
    bool wait = false;
    while (window.isOpen() && !quit) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (wait) {
                    quit = true;
                    break;
                }
                for (size_t i = 0; i < size; i++) {
                    for (size_t j = 0; j < size; j++) {
                        RectangleShape &fieldView = fieldViews[i][j];
                        if (contains(fieldView, Vector2<float>(Mouse::getPosition(window)), fieldSize, i, j, outlineSize)) {
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                DisarmResult disarmResult = board.disarm(i, j);
                                if (disarmResult == EMPTY) {
                                    fieldView.setFillColor(Color::Black);
                                    size_t value = board.getBombsAroundCount(i, j);
                                    Text &text = numbersView[i][j];
                                    text.setString(std::to_string(value));
                                    Vector2<float> fieldViewSize = fieldView.getSize();
                                    Vector2<float> fieldViewPosition = fieldView.getPosition();
                                    Vector2<float> adjustment = getTextAdjustment(text);
                                    text.setPosition(fieldViewPosition.x + fieldViewSize.x / 2 - adjustment.x,
                                                     fieldViewPosition.y + fieldViewSize.y / 2 - adjustment.y);
                                } else if (disarmResult == BARE) {
                                    for (size_t k = 0; k < size; k++) {
                                        for (size_t l = 0; l < size; l++) {
                                            if (board.getIsBare(k, l)) {
                                                fieldViews[k][l].setFillColor(colorGrey);
                                            }
                                        }
                                    }
                                } else if (disarmResult == EXPLODED) {
                                    fieldView.setFillColor(Color::Red);
                                    wait = true;
                                }
                            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                                MarkResult markResult = board.mark(i, j);
                                if (markResult == MARKED || markResult == ALL_MARKED) {
                                    fieldView.setFillColor(sf::Color::Blue);
                                    if (markResult == ALL_MARKED) {
                                        centerText(window, message, font, color, "YOU ROCK!");
                                        wait = true;
                                    }
                                } else if (markResult == UNMARKED) {
                                    fieldView.setFillColor(sf::Color::Cyan);
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear(Color(128, 128, 128));
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                window.draw(fieldViews[i][j]);
                window.draw(numbersView[i][j]);
            }
        }
        if (wait) {
            window.draw(message);
        }
        window.display();
    }
    return EXIT_SUCCESS;
}

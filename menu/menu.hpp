#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3

class Menu {
public:
    Menu(float width, float height, std::vector<sf::String> itemNames, int id);

    void draw(sf::RenderWindow &window);

    void up();

    void down();

    int choose();

    int getId();

private:
    sf::Font font;
    sf::Text items[MAX_NUMBER_OF_ITEMS];
    int selected;
    int itemCount;
    int identifier;

    void move(bool up);
};


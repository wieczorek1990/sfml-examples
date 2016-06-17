#include <SFML/Graphics.hpp>
#include "menu.hpp"

using namespace sf;
using namespace std;

int main() {
    unsigned int WINDOW_SIZE = 600;
    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SAPPER");
    Menu firstMenu(window.getSize().x, window.getSize().y,
                   vector<String> {"New Game", "Exit"}, 0);
    Menu secondMenu(window.getSize().x, window.getSize().y,
                    vector<String> {"Ignacy", "?", "Back"}, 1);
    Menu *menu = &firstMenu;
    int chosen = -1;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::KeyReleased:
                    switch (event.key.code) {
                        case Keyboard::Up:
                            menu->up();
                            break;
                        case Keyboard::Down:
                            menu->down();
                            break;
                        case Keyboard::Return:
                        case Keyboard::Space:
                            chosen = menu->choose();
                            if (menu->getId() == 0) {
                                if (chosen == 0) {
                                    menu = &secondMenu;
                                } else if (chosen == 1) {
                                    window.close();
                                }
                            } else if (menu->getId() == 1) {
                                if (chosen == 0) {
                                    window.close();
                                } else if (chosen == 1) {
                                    window.close();
                                } else if (chosen == 2) {
                                    menu = &firstMenu;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        window.clear();
        menu->draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}


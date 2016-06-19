#ifdef _WIN32

#include <SFML\Graphics.hpp>
#include <windows.h>

#else

#include <SFML/Graphics.hpp>

#endif

#include "menu.hpp"
#include "game.hpp"
#include "constants.hpp"

using namespace sf;
using namespace std;

#ifdef _WIN32

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {

#else

int main() {

#endif

    RenderWindow window(VideoMode(Constants::WINDOW_SIZE, Constants::WINDOW_SIZE), "SAPPER");
    Menu firstMenu(window.getSize().x, window.getSize().y,
                   vector<String> {"New Game", "Exit"}, 0);
    Menu secondMenu(window.getSize().x, window.getSize().y,
                    vector<String> {"Easy", "Normal", "Hard", "Back"}, 1);
    Menu *menu = &firstMenu;
    int chosen = -1;
    Game game;
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
                                    game.run(0);
                                } else if (chosen == 1) {
                                    game.run(1);
                                } else if (chosen == 2) {
                                    game.run(2);
                                } else if (chosen == 3) {
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

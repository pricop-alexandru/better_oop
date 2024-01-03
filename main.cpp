#include <chrono>

#include "game.h"
#include "menu.h"
int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(1920, 1080), "Setris Game");

    Menu gameMenu(mainWindow); // pornim meniul

    while (mainWindow.isOpen()) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (gameMenu.playButtonClicked()) {
                        // Trecem la joc
                        gameMenu.close(); // inchidem meniul
                        Game gameInterface(mainWindow); // pornim jocul
                        gameInterface.run(); // si intram in loop-ul de joc
                    }
                }
                // loc pentru eventuale alte butoane
            }
        }

        mainWindow.clear();
        gameMenu.run(); // desenam ce ne trb
        mainWindow.display();
    }

    return 0;
}/*as fi vrut, si actually am incercat sa folosesc pointeri in schimbarea de window in acest main, dar nu imi rula chestiile din
 * int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(1920, 1080), "Setris Game");
    std::unique_ptr<Interface> currentState = std::make_unique<Menu>(mainWindow);

    while (mainWindow.isOpen()) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
            else if (event.type == sf::Event::MouseButtonReleased) {
                Menu* menuState = dynamic_cast<Menu*>(currentState.get());
                if (menuState && menuState->playButtonClicked()) {
                    // Switch to the game state
                    currentState = std::make_unique<Game>(mainWindow);
                }
            }
        }

        mainWindow.clear();
        currentState->run();
        mainWindow.display();
    }

    return 0;
} Dar nu stiu de ce nu functioneaza wondow-ul de game, in sensul ca am testat cu std::cout-uri pe la elementele din game si la switchul de window, cum ar fi la
 drawborder in playfield si returneaza bine absolut toate, dar ecranul meu de joc tot negru este, also nu stiu cum as face o ierarhie cu <exception>*/
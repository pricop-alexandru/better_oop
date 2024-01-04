#include <chrono>
#include <memory> //asa am reparat 6 erori de asan check si wondows gnu, luati aminte copii
#include "gameover.h"
#include "game.h"
#include "menu.h"
void startGame(sf::RenderWindow& window) {
    std::unique_ptr<Interface> currentState = std::make_unique<Game>(window);

    while (window.isOpen()) {
        currentState->run();

        Game* gamePtr = dynamic_cast<Game*>(currentState.get());
        if (gamePtr && gamePtr->isGameOver()) { //asta ca sa nu fie nullpointer chiar daca zice tidy ca e mereu true
            currentState = std::make_unique<GameOver>(window);
            currentState->run();
            break;
        }
    }
}
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
                        startGame(mainWindow); //deschidem functia cu care avem si jocul si pierderea jocului (desi e cam greu sa pierzi momentan (mai putin daca modific sa mai pun o culoare)
                    }
                }
            }
        }
        mainWindow.clear();
        gameMenu.run(); // desenam ce ne trb
        mainWindow.display();
    }

    return 0;
}
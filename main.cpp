#include <chrono>

#include "interface.h"
#include "menu.h"
int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(1920, 1080), "Tetris Game");

    Menu gameMenu(mainWindow); // Initialize the menu with the main window

    while (mainWindow.isOpen()) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (gameMenu.playButtonClicked()) {
                        // Transition to game interface
                        gameMenu.close(); // Close the menu
                        Interface gameInterface(mainWindow); // Start the game interface
                        gameInterface.run(); // Start running the game
                    }
                }
                // Handle other button clicks in menu if needed
            }
        }

        mainWindow.clear();
        gameMenu.run(); // Draw the menu elements
        mainWindow.display();
    }

    return 0;
}
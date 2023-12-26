#include "game.h"

Game::Game(sf::RenderWindow& mainWindow) : window(mainWindow), playField(mainWindow) {
    var=0;
}
void Game::read() { std::cin>>var;}

void Game::write() const {std::cout<<var;}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); // Clear the window with a black color

        playField.drawBorder();

        window.display(); // Display what was drawn
    }
}

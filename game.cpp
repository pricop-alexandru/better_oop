#include "game.h"

Game::Game(sf::RenderWindow& mainWindow) : window(mainWindow), playField(mainWindow) {
    var=0;
}
void Game::read() { std::cin>>var;}

void Game::write() const {std::cout<<var;}

void Game::run() {
    sf::Time delayTime = sf::milliseconds(250);
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        playField.drawBorder();
        bool hasMoved;
        playField.move_down(hasMoved);
        if (!hasMoved)
            playField.spawnRandomPiece();
        playField.draw();
        window.display(); // Afisam frumos pana nu devine complicat
        sf::sleep(delayTime);
    }
}

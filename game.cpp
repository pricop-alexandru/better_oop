#include "game.h"

Game::Game(sf::RenderWindow& mainWindow) : window(mainWindow), playField(mainWindow) {
    var=0;
}
void Game::read() { std::cin>>var;}

void Game::write() const {std::cout<<var;}

void Game::run() {
    sf::Time delayTime = sf::milliseconds(150);
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A)
                    playField.move_left();
                if (event.key.code == sf::Keyboard::D)
                    playField.move_right();
            }
        }

        window.clear(sf::Color::Black);

        playField.drawBorder();
        bool hasMoved;
        playField.move_down(hasMoved);
        playField.checkAndResolveCollisions();
        playField.markLines();
        if (!hasMoved)
            playField.spawnRandomPiece();
        playField.draw();
        window.display(); // Afisam frumos pana nu devine complicat
        playField.clearLines(); // Pentru ca altfel nu am apuca sa vedem vreo linie curatata pana nu ar da display daca l-am pune inainte, dar asa vedem in acelasi display liniile de curatat, si in urmatorul pentru operatiile de langa e deja curat.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::sleep(sf::milliseconds(25)); // mai rapid putin
        } else {
            sf::sleep(delayTime); // Viteza normala (inca consistent din cate observ in operatii simplute, daca era mai complex aveam nevoie de std::Clock
        }
    }
}

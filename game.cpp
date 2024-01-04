#include "game.h"

Game::Game(sf::RenderWindow& mainWindow) : window(mainWindow), playField(mainWindow) {
    var=0;
    if (!font.loadFromFile("Resources/Doctor Glitch.otf")){
        throw std::runtime_error("Failed to load font"); //tot nu avem ierarhie
    }
    clearedLinesText.setFont(font);
    clearedLinesText.setCharacterSize(30); // Choose an appropriate size
    clearedLinesText.setFillColor(sf::Color::White); // Choose text color
    clearedLinesText.setStyle(sf::Text::Regular);
    clearedLinesText.setPosition(50, 950);
}
void Game::read() { std::cin>>var;}

void Game::write() const {std::cout<<var;}

void Game::run() {
    while (window.isOpen() && !playField.isGameOver()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A)
                    playField.move_left();
                if (event.key.code == sf::Keyboard::D)
                    playField.move_right();
                if (event.key.code == sf::Keyboard::R)
                    playField.restartGame();
            }
        }

        window.clear(sf::Color::Black);
        playField.drawBorder();
        playField.drawText();
        clearedLinesText.setString("Lines cleared: " + std::to_string(playField.getClearedLines()));
        bool hasMoved;
        playField.move_down(hasMoved);
        playField.checkAndResolveCollisions();
        playField.markLines();
        if (!hasMoved)
            playField.spawnRandomPiece();
        playField.draw();
        window.draw(clearedLinesText);
        window.display(); // Afisam frumos pana nu devine complicat
        playField.clearLines(); // Pentru ca altfel nu am apuca sa vedem vreo linie curatata pana nu ar da display daca l-am pune inainte, dar asa vedem in acelasi display liniile de curatat, si in urmatorul pentru operatiile de langa e deja curat.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::sleep(sf::milliseconds(25)); // mai rapid putin
        } else {
            sf::sleep(sf::milliseconds(150)); // Viteza normala (inca consistent din cate observ in operatii simplute, daca era mai complex aveam nevoie de std::Clock
        }
    }
}

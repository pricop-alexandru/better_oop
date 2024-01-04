#include "gameover.h"

GameOver::GameOver(sf::RenderWindow& mainWindow): window(mainWindow) {
    if (!font.loadFromFile("Resources/Doctor Glitch.otf")){
        throw std::runtime_error("Failed to load font");
    }
}

void GameOver::run() {
    sf::Text prompt("Game Over! Enter your name:", font);
    prompt.setPosition(550, 400);
    prompt.setCharacterSize(50);
    prompt.setFillColor(sf::Color::White);

    sf::Text nameText("", font);
    nameText.setPosition(550, 500);
    nameText.setCharacterSize(50);
    nameText.setFillColor(sf::Color::White);
    std::string playerName;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !playerName.empty()) {  // Handle backspace
                    playerName.pop_back();
                } else if (event.text.unicode < 128) {  // Handle regular character input
                    playerName += static_cast<char>(event.text.unicode);
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                break;
        }

        nameText.setString(playerName);

        window.clear();
        window.draw(prompt);
        window.draw(nameText);
        window.display();
    }

    player.setName(playerName);
}
void GameOver::read() {std::cin>>var;}
void GameOver::write() const {std::cout<<var;}
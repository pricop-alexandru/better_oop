#include "gameover.h"

GameOver::GameOver(sf::RenderWindow& mainWindow): window(mainWindow) {
    if (!font.loadFromFile("Resources/Doctor Glitch.otf")){
        throw std::runtime_error("Failed to load font");
    }
    var=0;
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
                if (event.text.unicode == '\b' && !playerName.empty()) {  // sa se stearga din playername in timp real
                    playerName.pop_back();
                } else if (event.text.unicode < 128) {  // sa adaugam orice caracter (nu punctuatii)
                    playerName += static_cast<char>(event.text.unicode);
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                break;
            }
        }

        nameText.setString(playerName); //dupa toate operatiile, le afiseaza

        // salvam in leaderboard
        std::ofstream file("leaderboard.txt", std::ios::app);
        file << playerName << ": " << player.getScore() << std::endl;

        window.clear();
        window.draw(prompt);
        window.draw(nameText);
        window.display();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            std::cout << "Exiting GameOver screen" << std::endl; //aparent cu el doar in poll event iese din loopul de events, pe scurt ecranul ramane doar devine unresponsive
            break; // prin urmare am avut nevoie de doua eventuri de enter
        }
    }

    player.setName(playerName);
}
GameOver* GameOver::clone() const {
    return new GameOver(*this);
}
void GameOver::read() {std::cin>>var;}
void GameOver::write() const {std::cout<<var;}
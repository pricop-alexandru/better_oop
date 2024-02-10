#include "Leaderboard.h"

Leaderboard::Leaderboard(sf::RenderWindow& mainWindow): window(mainWindow) {
    if (!font.loadFromFile("Resources/Doctor Glitch.otf")){
        throw std::runtime_error("Failed to load font");
    }
    var=0;
}

void Leaderboard::run() {
    sf::Text prompt("Leaderboard", font);
    prompt.setPosition(550, 400);
    prompt.setCharacterSize(50);
    prompt.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(prompt);

        // Loop through the scores and display them
        std::ifstream file("leaderboard.txt");
        std::string line;
        int i = 0;
        while (std::getline(file, line)) {
            sf::Text scoreText(line, font);
            scoreText.setPosition(550, 500 + i * 50);
            scoreText.setCharacterSize(50);
            scoreText.setFillColor(sf::Color::White);
            window.draw(scoreText);
            i++;
        }

        window.display();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            std::cout << "Exiting Leaderboard screen" << std::endl; //aparent cu el doar in poll event iese din loopul de events, pe scurt ecranul ramane doar devine unresponsive
            break; // prin urmare am avut nevoie de doua eventuri de enter
        }
    }
}
Leaderboard* Leaderboard::clone() const {
    return new Leaderboard(*this);
}
void Leaderboard::read() {std::cin>>var;}
void Leaderboard::write() const {std::cout<<var;}
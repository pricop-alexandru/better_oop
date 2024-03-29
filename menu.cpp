#include "menu.h"
// #include <stdexcept>
#include "exceptions.h"

Menu::Menu(sf::RenderWindow& mainWindow) : window(mainWindow) {
    var=0;
    if (!backgroundTexture.loadFromFile("Resources/projectimage.jpg")) {
        // throw std::runtime_error("Failed to load background image");
        throw FailedToLoadResourceException("Failed to load background image");
    }
    backgroundSprite.setTexture(backgroundTexture);
    //background^
    if (!font.loadFromFile("Resources/Doctor Glitch.otf")){
        // throw std::runtime_error("Failed to load font");
        throw FailedToLoadResourceException("Failed to load font");
    }

    titleText.setFont(font);
    titleText.setString("Setris");
    titleText.setCharacterSize(250);
    titleText.setFillColor(sf::Color::White);
    float titleTextWidth = titleText.getLocalBounds().width;
    titleText.setOrigin(titleTextWidth / 2.0f, 0);
    titleText.setPosition(window.getSize().x / 2.0f, 200.0f);
    //font^
    float buttonWidth = 700.0f;
    float buttonHeight = 50.0f;
    float verticalGap = 100.0f;
    playButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    playButton.setPosition((window.getSize().x - buttonWidth) / 2.0f, (window.getSize().y - buttonHeight) / 2.0f + 2.5f);
    playButton.setOutlineColor(sf::Color::Black);
    playButton.setOutlineThickness(2.0f);
    //play button^

    leaderboardButton.setSize(sf::Vector2f(600.0f, buttonHeight));
    leaderboardButton.setPosition((window.getSize().x - 600.0f) / 2.0f,(window.getSize().y + buttonHeight + verticalGap ) / 2.0f + 2.5f);
    leaderboardButton.setOutlineColor(sf::Color::Black);
    leaderboardButton.setOutlineThickness(2.0f);
    //leaderboard button^

    playText.setString("Play");
    playText.setFont(font);
    playText.setCharacterSize(50);
    playText.setFillColor(sf::Color::Black);

    float playTextWidth = playText.getLocalBounds().width;
    playText.setOrigin(playTextWidth / 2.0f, 0);
    playText.setPosition(window.getSize().x / 2.0f, 510.0f);

    leaderboardText.setString("Leaderboard");
    leaderboardText.setFont(font);
    leaderboardText.setCharacterSize(50);
    leaderboardText.setFillColor(sf::Color::Black);
    float leaderboardTextWidth = leaderboardText.getLocalBounds().width;
    leaderboardText.setOrigin(leaderboardTextWidth / 2.0f, 0);
    leaderboardText.setPosition(window.getSize().x / 2.0f, 610.0f);
    //texte pe masura^
}
void Menu::run(){
    window.draw(backgroundSprite);
    window.draw(titleText);

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionF = window.mapPixelToCoords(mousePosition);
    if (playButton.getGlobalBounds().contains(mousePositionF)) {
        playButton.setFillColor(sf::Color(150, 130, 200));
    } else {
        playButton.setFillColor(sf::Color(150, 80, 200));
    }
    window.draw(playButton);
    //^^arata putin mai luminos cand pun mouse-ul pe el
    if (leaderboardButton.getGlobalBounds().contains(mousePositionF)) {
        leaderboardButton.setFillColor(sf::Color(150, 130, 200));
    } else {
        leaderboardButton.setFillColor(sf::Color(150, 80, 200));
    }
    window.draw(leaderboardButton);
    //^^la fel la ambele
    window.draw(playText);
    window.draw(leaderboardText);

}
bool Menu::playButtonClicked() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionF = window.mapPixelToCoords(mousePosition);
    return playButton.getGlobalBounds().contains(mousePositionF);
}
void Menu::close() {
}
Menu* Menu::clone() const {
    return new Menu(*this);
}
void Menu::read() {std::cin>>var;}
void Menu::write() const {std::cout<<var;}

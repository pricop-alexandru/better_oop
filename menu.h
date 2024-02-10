#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "interface.h"

class Menu : public Interface {
private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text titleText;
    sf::Text playText;
    sf::Text leaderboardText;
    sf::RectangleShape playButton;
    sf::RectangleShape leaderboardButton;
    int var;

public:
    explicit Menu(sf::RenderWindow& mainWindow);

    void run() override;
    bool playButtonClicked(); // Example function to check if the "Play" button is clicked
    void close();
    Menu* clone() const override;
    void read() override;
    void write() const override;
};

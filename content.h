#pragma once
#include <SFML/Graphics.hpp>

class PlayField {
public:
    PlayField(sf::RenderWindow& window);
    void drawBorder();

private:
    sf::RenderWindow& window;
    sf::RectangleShape border;
};
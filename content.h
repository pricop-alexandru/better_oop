#pragma once
#include <SFML/Graphics.hpp>

class PlayField {
public:
    explicit PlayField(sf::RenderWindow& window);
    void drawBorder();

private:
    sf::RenderWindow& window;
    sf::RectangleShape border;
};
#include "content.h"

PlayField::PlayField(sf::RenderWindow& win) : window(win) {
    // Set the size of the border considering the line thickness
    float borderThickness = 10.0f;
    float borderWidth = 500.0f + borderThickness * 2;
    float borderHeight = 1000.0f + borderThickness * 2;
    border.setSize(sf::Vector2f(borderWidth, borderHeight));
    border.setPosition((win.getSize().x - borderWidth) / 2, (win.getSize().y - borderHeight) / 2);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(borderThickness);
    border.setOutlineColor(sf::Color::White);
}

void PlayField::drawBorder() {
    window.draw(border);
}
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

class Interface : public Game {
private:
    sf::RenderWindow& window;
    int var;
public:
    explicit Interface(sf::RenderWindow& mainWindow);
    void run() override;
    void read() override;
    void write() const override;
};
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "interface.h"
#include "content.h"

class Game : public Interface {
private:
    sf::RenderWindow& window;
    PlayField playField;
    int var;
public:
    explicit Game(sf::RenderWindow& mainWindow);
    void run() override;
    void read() override;
    void write() const override;
};
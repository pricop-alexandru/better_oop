#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "interface.h"

class Leaderboard : public Interface {
public:
    explicit Leaderboard(sf::RenderWindow& mainWindow);
    void run() override;
    void read() override;
    void write() const override;
    Leaderboard* clone() const override;
private:
    int var;
    sf::RenderWindow& window;
    sf::Font font;
};
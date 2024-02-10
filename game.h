#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "interface.h"
#include "content.h"

class Game : public Interface {
private:
    sf::RenderWindow& window;
    PlayField playField;
    int var;
    sf::Font font;
    sf::Text clearedLinesText;
public:
    bool isGameOver() {
        return playField.isGameOver(); //il folosim pt pointers
    }
    explicit Game(sf::RenderWindow& mainWindow);
    void run() override;
    void read() override;
    void write() const override;
    Game* clone() const override {
        return new Game(*this);
    }
};
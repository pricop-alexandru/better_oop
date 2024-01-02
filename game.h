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
    int var; //singurul scop al acestuia e sa nu lase constructorul gol :(
public:
    explicit Game(sf::RenderWindow& mainWindow);
    void run() override;
    void read() override;
    void write() const override;
};
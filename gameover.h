#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "interface.h"

class Player {
private:
    std::string name;
    int score;
public:
    Player() : score(0) {

    }
    void setName(const std::string& newName) {
        name = newName;
    }
    std::string getName() const {
        return name;
    }
    void setScore(int newScore) {
        score = newScore;
    }
    int getScore() const {
        return score;
    }
};

class GameOver : public Interface {
public:
    explicit GameOver(sf::RenderWindow& mainWindow);
    void run() override;
    void read() override;
    void write() const override;
    GameOver* clone() const override;
    Player player; //gata si ultima compunere
private:
    int var;
    sf::RenderWindow& window;
    sf::Font font;
};
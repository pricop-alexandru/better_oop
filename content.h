#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
class PlayField {
    friend std::ostream& operator<<(std::ostream& os, const PlayField& playField);
public:
    explicit PlayField(sf::RenderWindow& window);
    ~PlayField(){ std::cout<<"Operation complete."<<std::endl; }
    PlayField& operator=(const PlayField& other);
    void drawBorder();
    void draw();
    void move_down(bool& hasMoved);
    void drawCell(int x, int y, int cellValue);
    void spawnRandomPiece();
    void checkAndResolveCollisions();
    void move_left();
    void move_right();
    void markLines();
    void clearLines();
    int getClearedLines() const { return clearedLines; } //il voi folosi la printat leaderboard (poate pot folosi acolo smart pointers?)
private:
    sf::RenderWindow& window;
    sf::RectangleShape border;
    std::vector<std::vector<int>> grid; // 50 pe 100 (din 500 pe 1000 pixeli :( )
    int getRandomColor();
    int clearedLines;
    void spawnLineShape(int color);
    bool findGroup(int x, int y, int color, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& group, bool& edgeLeft, bool& edgeRight);
    static const int gridRows = 100;
    static const int gridCols = 50;
    static const int cellSize = 10; // macar cu proportia asta grid-ul nu face urat ca ia 100 de pixeli de o data
};
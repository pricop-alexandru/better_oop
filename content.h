#pragma once
#include <SFML/Graphics.hpp>
#include <random>
class PlayField {
public:
    explicit PlayField(sf::RenderWindow& window);
    void drawBorder();
    void draw();
    void move_down(bool& hasMoved);
    void drawCell(int x, int y, int cellValue);
    void spawnRandomPiece();
private:
    sf::RenderWindow& window;
    sf::RectangleShape border;
    std::vector<std::vector<int>> grid; // 50 pe 100 (din 500 pe 1000 pixeli :( )
    int getRandomColor();
    void spawnLineShape(int color);
    static const int gridRows = 100;
    static const int gridCols = 50;
    static const int cellSize = 10; // macar cu proportia asta grid-ul nu face urat ca ia 100 de pixeli de o data
};
#include "content.h"

PlayField::PlayField(sf::RenderWindow& win) : window(win) {
    // cu 10 arata cel mai uman
    float borderThickness = 10.0f;
    float borderWidth = 500.0f + borderThickness * 2;
    float borderHeight = 1000.0f + borderThickness * 2;
    border.setSize(sf::Vector2f(borderWidth, borderHeight));
    border.setPosition((win.getSize().x - borderWidth) / 2, (win.getSize().y - borderHeight) / 2);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(borderThickness);
    border.setOutlineColor(sf::Color::White);
    grid.resize(gridRows, std::vector<int>(gridCols, 0));
}
void PlayField::drawBorder() {
    window.draw(border);
}
void PlayField::draw() {
    for (int y = 0; y < gridRows; ++y) {
        for (int x = 0; x < gridCols; ++x) {
            drawCell(x, y, grid[y][x]);
        }
    }
}
void PlayField::drawCell(int x, int y, int cellValue) {
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setPosition(710 + x * cellSize, 40 + y * cellSize);

    // Set cell color based on its value
    switch(cellValue) {
        case 1: cell.setFillColor(sf::Color::Red); break;
        case 2: cell.setFillColor(sf::Color::Green); break;
        case 3: cell.setFillColor(sf::Color::Blue); break;
        case 4: cell.setFillColor(sf::Color::Red); break;
        case 5: cell.setFillColor(sf::Color::Green); break;
        case 6: cell.setFillColor(sf::Color::Blue); break;
        default: cell.setFillColor(sf::Color::Black); // restul e gol
    }

    window.draw(cell);
}
void PlayField::move_down(bool& hasMoved) {
    hasMoved = false; //bool-ul magic cu care apelam spawnul de forme

    for (int y = gridRows - 2; y >= 0; --y) { // Start from second-to-last row
        for (int x = 0; x < gridCols; ++x) {
            if (grid[y][x] != 0) { // daca nu e gol
                // vedem dedesubt
                if (y + 1 < gridRows && grid[y + 1][x] == 0) {
                    grid[y + 1][x] = grid[y][x];
                    grid[y][x] = 0;
                    hasMoved = true;
                }
                    // vedem pe stanga
                else if (x > 0 && y + 1 < gridRows && grid[y + 1][x - 1] == 0 && grid[y][x - 1] == 0) {
                    grid[y + 1][x - 1] = grid[y][x];
                    grid[y][x] = 0;
                    hasMoved = true;
                }
                    // vedem pe dreapta
                else if (x + 1 < gridCols && y + 1 < gridRows && grid[y + 1][x + 1] == 0 && grid[y][x + 1] == 0) {
                    grid[y + 1][x + 1] = grid[y][x];
                    grid[y][x] = 0;
                    hasMoved = true;
                }
            }
        }
    }
}
int PlayField::getRandomColor() {
    static std::uniform_int_distribution<int> colorDist(4, 6); // e manevra ca 4 5 si 6 sunt 1 2 si 3, dar se misca, ajuta cand vrem sa controlam piesa din aer
    static std::mt19937 rng(std::random_device{}()); //
    return colorDist(rng);
}

void PlayField::spawnRandomPiece() {
    int color = getRandomColor();
    // We spawn the line for now :)
    spawnLineShape(color);
}
void PlayField::spawnLineShape(int color) {
    // o sa fie transformat mai incolo in randomizer de forme
    int startY = 0; // sus
    int startX = gridCols / 2 - 10; // centrat
    for (int x = startX; x < startX + 20; ++x) {
        for (int y = startY; y < startY + 5; ++y) {
            grid[y][x] = color;
        }
    }
}

#include "content.h"
PlayField::PlayField(sf::RenderWindow& win) : window(win), clearedLines(0) {
    // cu 10 arata cel mai uman
    float borderThickness = 10.0f;
    float borderWidth = 500.0f + borderThickness/2;
    float borderHeight = 1000.0f + borderThickness/2;
    border.setSize(sf::Vector2f(borderWidth, borderHeight));
    border.setPosition((win.getSize().x - borderWidth) / 2, (win.getSize().y - borderHeight) / 2);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(borderThickness);
    border.setOutlineColor(sf::Color::White);
    grid.resize(gridRows, std::vector<int>(gridCols, 0));
    shapeFunctions = {&PlayField::spawnLineShape, &PlayField::spawnOShape, &PlayField::spawnLShape, &PlayField::spawnTShape};
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
    switch(cellValue) {
        case -1: cell.setFillColor(sf::Color::Cyan); break;
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
    hasMoved = false;

    for (int y = gridRows - 2; y >= 0; --y) { // nu incepem de jos ca n-are sens, ce e pe linia de jos nu mai are unde sa miste
        for (int x = 0; x < gridCols; ++x) {
            if (grid[y][x] > 0) { // daca celula noastra nu e goala
                // verificam daca avem ceva dedesubt valid
                if (y + 1 < gridRows && grid[y + 1][x] == 0) {
                    grid[y + 1][x] = grid[y][x];
                    grid[y][x] = 0;
                    hasMoved = true;
                }
                    // verificam diagonal stanga
                else if (x > 0 && y + 1 < gridRows && grid[y + 1][x - 1] == 0 && grid[y][x - 1] == 0) {
                    grid[y + 1][x - 1] = grid[y][x];
                    grid[y][x] = 0;
                    hasMoved = true;
                }
                    // verificam diagonal dreapta
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
    static std::mt19937 rng(std::random_device{}()); // nush ce face codul de la std ...
    return colorDist(rng);
}

void PlayField::spawnRandomPiece() {
    int color = getRandomColor();
        // randomizam una din functii:)
        std::srand(static_cast<unsigned int>(std::time(nullptr)));  // Seed pt generare
        int randomIndex = std::rand() % shapeFunctions.size();
        // apelam functia random
        ShapeFunction selectedFunction = shapeFunctions[randomIndex];
        (this->*selectedFunction)(color);
}
void PlayField::spawnLineShape(int color) {
    int startY = 0; // sus
    int startX = gridCols / 2 - 10; // centrat
    for (int x = startX; x < startX + 20; ++x) {
        for (int y = startY; y < startY + 5; ++y) {
            grid[y][x] = color;
        }
    }
}
void PlayField::spawnOShape(int color) {
    int startY = 0; // sus
    int startX = gridCols / 2 - 5; // centrat
    for (int x = startX; x < startX + 10; ++x) {
        for (int y = startY; y < startY + 10; ++y) {
            grid[y][x] = color;
        }
    }
}
void PlayField::spawnTShape(int color) {
    int startY = 0; // sus
    int startX = gridCols / 2 - 5; // centrat
    for (int x = startX; x < startX + 15; ++x) {
        for (int y = startY + 5; y < startY + 10; ++y) {
            grid[y][x] = color;
        }
        for (int y = startY; y < startY + 5 ; ++y) {
            if(x >= startX + 5 && x < startX + 10)
                grid[y][x] = color;
        }
    }
}
void PlayField::spawnLShape(int color) {
    int startY = 0; // sus
    int startX = gridCols / 2 - 5; // centrat
    for (int x = startX; x < startX + 15; ++x) {
        for (int y = startY + 5; y < startY + 10; ++y) {
            grid[y][x] = color;
        }
        for (int y = startY; y < startY + 5 ; ++y) {
            if(x >= startX + 10)
                grid[y][x] = color;
        }
    }
}
void PlayField::checkAndResolveCollisions() {
    bool collisionDetected = false;

    // verificam de jos in sus ca sa fie mai rapid
    for (int y = gridRows - 1; y >= 0; --y) {
        for (int x = 0; x < gridCols; ++x) {
            if (grid[y][x] >= 4) { // pe cei care sunt in cadere
                // daca au terminat grid-ul sau au dat de alti pixeli care stau pe loc
                if (y == gridRows - 1 || (grid[y + 1][x] >= 1 && grid[y + 1][x] <= 3) || grid[y+1][x] == -1) {
                    collisionDetected = true;
                    break;
                }
            }
        }
        if (collisionDetected) {
            break;
        }
    }
    // Daca s-au lovit, modificam tot fara ezitare, ca nu putem sa lasam doar o parte din forma sa fie afectata
    if (collisionDetected) {
        for (int y = 0; y < gridRows; ++y) {
            for (int x = 0; x < gridCols; ++x) {
                if (grid[y][x] >= 4) {
                    grid[y][x] -= 3; // il facem nemiscator
                }
            }
        }
    }
}
void PlayField::move_left() {
    // verificam
    bool canMoveLeft = false;
    for (int y = 0; y < gridRows; ++y) {
        for (int x = 1; x < gridCols; ++x) {
            if (grid[y][x] >= 4 && grid[y][x - 1] == 0) {
                canMoveLeft = true;
                break; // iesim
            }
        }
        if (canMoveLeft) {
            break; // iesim
        }
    }
    // facem
    if (canMoveLeft) {
        for (int y = gridRows - 1; y >= 0; --y) {
            for (int x = 0; x < gridCols - 1; ++x) {
                if (grid[y][x + 1] >= 4) {
                    grid[y][x] = grid[y][x + 1];
                    grid[y][x + 1] = 0;
                }
            }
        }
    }
}
void PlayField::move_right() {
    // verificam
    bool canMoveRight = false;
    for (int y = 0; y < gridRows; ++y) {
        for (int x = gridCols - 2; x >= 0; --x) {
            if (grid[y][x] >= 4 && grid[y][x + 1] == 0) {
                canMoveRight = true;
                break; // iesim
            }
        }
        if (canMoveRight) {
            break; // iesim
        }
    }

    // facem
    if (canMoveRight) {
        for (int y = gridRows - 1; y >= 0; --y) {
            for (int x = gridCols - 1; x > 0; --x) {
                if (grid[y][x - 1] >= 4) {
                    grid[y][x] = grid[y][x - 1];
                    grid[y][x - 1] = 0;
                }
            }
        }
    }
}
void PlayField::markLines() {
    std::vector<std::vector<bool>> visited(gridRows, std::vector<bool>(gridCols, false));

    for (int y = 0; y < gridRows; ++y) {
        for (int x = 0; x < gridCols; ++x) {
            if (!visited[y][x] && grid[y][x] > 0) {
                std::vector<std::pair<int, int>> group;
                bool edgeLeft = false, edgeRight = false;
                if (findGroup(x, y, grid[y][x], visited, group, edgeLeft, edgeRight)) {
                    // curatam (adica coloram frumos)
                    for (auto& cell : group) { //parcurgerea de : in for am prins-o de la structuri de date si opereaza foarte interesant in sensul ca doar le ia pe toate intr-o anumita proximitate sau ordine (inca nu sunt sigur)
                        grid[cell.second][cell.first] = -1;
                    }
                }
            }
        }
    }
}
// Flood fill cred, l-am gasit pe un site pentru astfel de probleme dar a trebuit sa il modific pentru verificari doar, cu depth searching
bool PlayField::findGroup(int x, int y, int color, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& group, bool& edgeLeft, bool& edgeRight) {
    if (x < 0 || x >= gridCols || y < 0 || y >= gridRows || visited[y][x] || grid[y][x] != color) {
        return false; //daca vizitam ceva vizitat sau nu vizitam culoarea care ne intereseaza, plecam
    }

    visited[y][x] = true;
    group.push_back(std::make_pair(x, y)); //care e diferenta dintre push_back si emplace_back? La make_pair deja inteleg ca majoritatea comenzilor sunt termeni literalmente de engleza

    if (x == 0) edgeLeft = true;
    if (x == gridCols - 1) edgeRight = true;

    findGroup(x - 1, y, color, visited, group, edgeLeft, edgeRight);
    findGroup(x + 1, y, color, visited, group, edgeLeft, edgeRight);
    findGroup(x, y - 1, color, visited, group, edgeLeft, edgeRight);
    findGroup(x, y + 1, color, visited, group, edgeLeft, edgeRight); //cu bitwise operation |= da crash

    return edgeLeft && edgeRight; //in functie de margini doar in contextul in care sunt legate la capete curata
}
void PlayField::clearLines() {
    bool ok = false;
    for(int y = 0; y < gridRows; y++)
        for(int x = 0; x < gridCols; x++)
            if(grid[y][x] == -1){
                grid[y][x]++;
                ok = true;
            }
    if(ok)
    {
        clearedLines++;
        std::cout<<clearedLines<<std::endl; //asta ca debugging ca merge momentan
    }
}
std::ostream& operator<<(std::ostream& os, const PlayField& playField) {
    for (int y = 0; y < PlayField::gridRows; ++y) {
        for (int x = 0; x < PlayField::gridCols; ++x) {
            os << playField.grid[y][x] << " ";
        }
        os << std::endl;
    }
    return os;
}
PlayField& PlayField::operator=(const PlayField& other) {
    if (this != &other) {
        this->grid = other.grid;
        this->clearedLines = other.clearedLines;
    }
    return *this;
}
void PlayField::restartGame() {
    for (int y = 0; y < gridRows; ++y) {
        for (int x = 0; x < gridCols; ++x) {
            grid[y][x] = 0;
        }
    }
    clearedLines = 0;
}
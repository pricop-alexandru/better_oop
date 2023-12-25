#pragma once
#include<iostream>
#include<fstream>
class Game {
public:
    virtual void run() = 0;
    virtual void read() = 0;
    virtual void write() const = 0;
    virtual ~Game() {};
    friend std::istream& operator>>(std::istream& in, Game& obj){ obj.read(); return in;}
    friend std::ostream& operator<<(std::ostream& out, const Game& obj){ obj.write(); return out;}
};
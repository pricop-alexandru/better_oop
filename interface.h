#pragma once
#include<iostream>
#include<fstream>
class Interface {
public:
    virtual void run() = 0;
    virtual void read() = 0;
    virtual void write() const = 0;
    virtual ~Interface() {};
    friend std::istream& operator>>(std::istream& in, Interface& obj){ obj.read(); return in;}
    friend std::ostream& operator<<(std::ostream& out, const Interface& obj){ obj.write(); return out;}
};
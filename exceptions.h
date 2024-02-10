#pragma once
#include <exception>
#include <string>

class TetrisException : public std::exception {
public:
    [[nodiscard]]  const char* what() const noexcept override {
        return "A Tetris exception has occurred.";
    }
};

class OutOfBoundsException : public TetrisException {
public:
    [[nodiscard]]  const char* what() const noexcept override {
        return "OutOfBounds: A block was placed out of bounds.";
    }
};

class BlockCollisionException : public TetrisException {
public:
    [[nodiscard]]  const char* what() const noexcept override {
        return "BlockCollision: A block collided with another block.";
    }
};

class GameOverException : public TetrisException {
public:
    [[nodiscard]]  const char* what() const noexcept override {
        return "GameOver: All blocks reached the top.";
    }
};

class FailedToLoadResourceException : public std::exception {
public:
    explicit FailedToLoadResourceException(const std::string& extraInfo) 
        : message_("FailedToLoadResource: A resource failed to load.\n Extra Info: " + extraInfo) {}
    
    [[nodiscard]]  const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};
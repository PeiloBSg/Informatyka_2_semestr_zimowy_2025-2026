#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

struct BlockData {
    float x, y;
    int hp;
};

class Paddle;
class Ball;
class Brick;

class GameSnapshot {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    GameSnapshot(const Paddle& paddle, const Ball& ball, const std::vector<Brick>& bricks);
    GameSnapshot() = default; // Domyœlny konstruktor dla wczytywania

    // Gettery
    sf::Vector2f getPaddlePosition() const;
    sf::Vector2f getBallPosition() const;
    sf::Vector2f getBallVelocity() const;
    const std::vector<BlockData>& getBlocks() const;

    // Metody zapisu i odczytu
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};
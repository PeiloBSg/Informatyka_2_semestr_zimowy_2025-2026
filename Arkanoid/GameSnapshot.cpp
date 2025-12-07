#include "GameSnapshot.hpp"
#include "Paletka.hpp"
#include "Pilka.hpp"
#include "Cegla.hpp"
#include <fstream>

GameSnapshot::GameSnapshot(const Paddle& paddle, const Ball& ball, const std::vector<Brick>& bricks) {
    // Przechwyæ pozycjê paletki
    paddlePosition = paddle.getPosition();
    // Przechwyæ pozycjê i prêdkoœæ pi³ki
    ballPosition = ball.getPosition();
    ballVelocity = ball.getVelocity();
    // Przechwyæ stan wszystkich bloków
    blocks.clear();
    for (const auto& brick : bricks) {
        if (!brick.czyZniszczony()) {
            sf::Vector2f brickPos = brick.getPosition();
            BlockData blockData;
            blockData.x = brickPos.x;
            blockData.y = brickPos.y;
            blockData.hp = brick.getHP();
            blocks.push_back(blockData);
        }
    }
}

//Gettery
sf::Vector2f GameSnapshot::getPaddlePosition() const {
    return paddlePosition;
}

sf::Vector2f GameSnapshot::getBallPosition() const {
    return ballPosition;
}

sf::Vector2f GameSnapshot::getBallVelocity() const {
    return ballVelocity;
}

const std::vector<BlockData>& GameSnapshot::getBlocks() const {
    return blocks;
}

//Metody
bool GameSnapshot::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Zapis Paletki
    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";

    // Zapis Pi³ki
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    // Zapis liczby bloków
    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    // Zapis bloków
    for (const auto& block : blocks) {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    return true;
}

// Metoda odczytu z pliku
bool GameSnapshot::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string label;

    // 1. Wczytaj Paletkê
    if (!(file >> label >> paddlePosition.x >> paddlePosition.y) || label != "PADDLE") {
        file.close();
        return false;
    }
    // 2. Wczytaj Pi³kê
    if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y) || label != "BALL") {
        file.close();
        return false;
    }
    // 3. Wczytaj Bloki
    int blocksCount;
    if (!(file >> label >> blocksCount) || label != "BLOCKS_COUNT") {
        file.close();
        return false;
    }
    blocks.clear();
    for (int i = 0; i < blocksCount; ++i) {
        float x, y;
        int hp;
        if (!(file >> x >> y >> hp)) {
            file.close();
            return false;
        }
        blocks.push_back({ x, y, hp });
    }
    file.close();
    return true;
}

int GameSnapshot::calculateScore() const {
    int remainingScore = 0;

    for (const auto& block : blocks) {
        // hp=3 -> 0 punktów
        // hp=2 -> 30 punktów  
        // hp=1 -> 50 punktów
        // hp=0 -> 60 punktów

        if (block.hp == 3) {
            remainingScore += 60;
        }
        else if (block.hp == 2) {
            remainingScore += 30;
        }
        else if (block.hp == 1) {
            remainingScore += 10;  
        }
        else if (block.hp == 0) {
            remainingScore += 0; 
        }
    }
    return 1920 - remainingScore;
}
void GameSnapshot::saveGame(const Paddle& paddle, const Ball& ball, const std::vector<Brick>& bricks, const std::string& filename) {
    if (GameSnapshot(paddle, ball, bricks).saveToFile(filename)) {
        std::cout << "Gra zapisana!" << std::endl;
    }
    else {
        std::cout << "Blad zapisu gry!" << std::endl;
    }
}

int GameSnapshot::loadGame(Paddle& paddle, Ball& ball, std::vector<Brick>& bricks, float blockWidth, float blockHeight, const std::string& filename) {
    if (loadFromFile(filename)) {
        paddle.setPosition(getPaddlePosition());
        ball.setPosition(getBallPosition());
        ball.setVelocity(getBallVelocity());
        bricks.clear();
        for (const auto& blockData : getBlocks()) {
            bricks.emplace_back(
                sf::Vector2f(blockData.x, blockData.y),
                sf::Vector2f(blockWidth, blockHeight),
                blockData.hp
            );
        }
        int loadedScore = calculateScore();
        std::cout << "Gra wczytana!" << std::endl;
        return loadedScore;
    }
    else {
        std::cout << "Blad wczytywania gry! Plik nie istnieje." << std::endl;
        return 0;
    }
}
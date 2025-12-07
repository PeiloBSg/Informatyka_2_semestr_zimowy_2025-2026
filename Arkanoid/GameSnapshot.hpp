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
    sf::Vector2f paddlePosition;        // Pozycja paletki
    sf::Vector2f ballPosition;          // Pozyscja pi³ki
    sf::Vector2f ballVelocity;          // Prêdkoœæ pi³ki
    std::vector<BlockData> blocks;      // Dane o blokach
    int calculateScore() const;         // Oblicza na podsawie iloœci bloków jaki jest wynik

public:
    GameSnapshot(const Paddle& paddle, const Ball& ball, const std::vector<Brick>& bricks);
    GameSnapshot() = default;       // Domyœlny konstruktor dla wczytywania

    //Metody
    bool saveToFile(const std::string& filename) const;     // Zapisuje do pliku 
    bool loadFromFile(const std::string& filename);         // Odczytuje z pliku ale tylko do klasy 
    void saveGame(const Paddle& paddle, const Ball& ball, const std::vector<Brick>& bricks, const std::string& filename = "zapis.txt");                         // Za pomoc¹ metody saveToFile zapisuje do pliku i sprawdza czy zapis zosta³ wykonany
    int loadGame(Paddle& paddle, Ball& ball, std::vector<Brick>& bricks, float blockWidth, float blockHeight, const std::string& filename = "zapis.txt");      // Ustawia wszystkie zapisane dane na obiekty do klasy, ze zeiennych pobranych z metody loadGame, zwraca wynik 

    //Gettery
    sf::Vector2f getPaddlePosition() const;             // Pobiera pozycjê paletki
    sf::Vector2f getBallPosition() const;               // Pobiera pozycjê pi³ki
    sf::Vector2f getBallVelocity() const;               // Pobiera prêdkoœæ pi³ji
    const std::vector<BlockData>& getBlocks() const;    // Pobiera dane o blokach

};
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Pilka.hpp"
#include "Paletka.hpp"
#include "Cegla.hpp"
#include "Menu.hpp"
#include "StanGry.hpp"

class Game {
private:
    float wysokoscOkna;
    float szerokoscOkna;
    sf::RenderWindow window;
    Paddle paletka;
    Ball pilka;
    std::vector<Brick> bloki;
    Menu menu;
    GameState currentState;

    //Metody
    void resetGame();
    void processEvents();
    void controlPaddle();
    void controlBall();
    void update(sf::Time dt);
    void render();

public:
    Game();
    void run();
};
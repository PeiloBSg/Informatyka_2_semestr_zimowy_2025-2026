#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Pilka.hpp"
#include "Paletka.hpp"
#include "Cegla.hpp"
#include "Menu.hpp"
#include "StanGry.hpp"
#include "GameSnapshot.hpp"
#include "ScoresManager.hpp"

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
    GameSnapshot* currentGameSnapshot;
    ScoresManager scoresManager;
    int currentScore;
    sf::Font font;
    std::string Name;

    //Metody
    void resetGame();
    void processEvents();
    void controlPaddle();
    void controlBall();
    void update(sf::Time dt);
    void render();
    void renderScore();
    void renderScoresScreen();
    void saveGameState();
    void saveGame();
    void loadGame();

public:
    Game();
    void run();
};
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Pilka.hpp"
#include "Paletka.hpp"
#include "Cegla.hpp"
#include "Cegly.hpp"
#include "Menu.hpp"
#include "StanGry.hpp"
#include "GameSnapshot.hpp"
#include "ScoresManager.hpp"
#include "Dzwieki.hpp"

class Game {
private:
    //Sta³e
    const float WINDOW_WIDTH = 640.f;           // Szerokoœæ okna gry
    const float WINDOW_HEIGHT = 480.f;          // Wysokoœæ okna gry
    const int MAX_SCORE = 1920;                 // Maksymalny wynik (12*4*40)
    const float PADDLE_WIDTH = 100.f;           // Szerokoœæ paletki
    const float PADDLE_HEIGHT = 20.f;           // Wysokoœæ paletki
    const float PADDLE_SPEED = 8.f;             // Prêdkoœæ paletki
    const float BALL_RADIUS = 8.f;              // Promieñ pi³ki
    const float BALL_SPEED_X = 4.f;             // Szybkoœæ x pi³ki
    const float BALL_SPEED_Y = 3.f;             // Szybkoœæ y pi³ki
    const int BLOCKS_COLUMNS = 12;              // Iloœæ kolumn bloków
    static const int BLOCKS_ROWS = 4;           // Iloœæ wierszy bloków
    const float BLOCK_HEIGHT = 20.f;            // Wysokoœæ bloków
    const float BLOCK_WIDTH = (WINDOW_WIDTH - (BLOCKS_COLUMNS - 1) * 2.f) / BLOCKS_COLUMNS;     // Szerokoœæ bloków
    const float PADDLE_INIT_Y_OFFSET = 30.f;    // Odleg³oœæ paletki od do³u ekranu
    const float BALL_INIT_Y = 200.f;            // Y startowy pi³ki
    const float BLOCK_SPACING = 2.f;            // Odstêp miêdzy blokami
    const float BLOCK_OFFSET_Y = 60.f;          // Odleg³oœæ bloków od góry ekranu

    sf::RenderWindow window;            // Obiekt okno
    Paddle paletka;                     // Obiekt paletka
    Ball pilka;                         // Obiekt pi³ka
    std::vector<Brick> bloki;           // Obiekt blok
    Bricks bricks;                      // Obiekt bloków
    Menu menu;                          // Obiekt menu
    GameSnapshot snapshot;              // Obiekt snapshot
    GameState currentState;             // Obiekt enum stanu gry
    ScoresManager scoresManager;        // Obiekt zarz¹dznia wynikami
    sf::Font font;                      // Czcionka
    std::string Name;                   // Nick gracza
    Sounds dzwiek;                      // Obiekt dŸwiêków
    int currentScore;                   // Iloœæ punktów

    //Metody
    void loadResources();                               // £aduje czcionkê
    void resetGame();                                   // Resetuje grê
    void returnToMenu();                                // Powrót do menu
    void handleGameOver();                              // Sprawdza czy pi³ka wypad³a, lub czy gracz zniszczy³ wszystkie bloki
    void handleGlobalKeys(const sf::Event& event);      // Obs³uguje klawisze F5 oraz ESC
    void handleMenuInput(const sf::Event& event);       // W zale¿noœci jaki stan gry zosta³ wybrany, tworzy odpowiedni¹ akcjê
    void processEvents();                               // Przetwarza naciskanie przycisków
    void update(sf::Time dt);                           // Odpowiedzialna za aktualizowanie gry w stanie playing
    void render();                                      // Renderowanie

public:
    Game();

    void run();     // Po³¹czenie wszystkich metod

};
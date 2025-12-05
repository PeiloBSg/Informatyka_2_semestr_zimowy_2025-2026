#include "Game.hpp"

//Konstruktor
Game::Game()
    : window(sf::VideoMode(640.f, 480.f), "Arkanoid")
    , paletka(640.f / 2.f, 480.f - 30.f, 100.f, 20.f, 8.f)
    , pilka(640.f / 2.f, 200.f, 4.f, 3.f, 8.f)
    , menu(window.getSize().x, window.getSize().y)
    , currentState(GameState::Menu)
    , currentScore(0)
    , Name("Pawel")
{
    float szerokoscOkna = 640.f;
    float wysokoscOkna = 480.f;

    window.setFramerateLimit(60);

    // £adowanie czcionki
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Blad ladowania czcionki!" << std::endl;
    }
    // Przekazywanie czcionki do ScoresManager
    scoresManager.setFont(font);
}

//metody

void Game::resetGame() {
    paletka = Paddle(640.f / 2.f, 480.f - 30.f, 100.f, 20.f, 8.f);
    pilka = Ball(640.f / 2.f, 200.f, 4.f, 3.f, 8.f);
    currentScore = 0;

    bloki.clear();

    const int ILOSC_KOLUMN = 12;
    const int ILOSC_WIERSZY = 4;
    float ROZMIAR_BLOKU_X = (640.f - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 20.f;

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        int i;
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
            switch (y) {
            case 0:
                i = 3;
                break;
            case 1:
                i = 3;
                break;
            case 2:
                i = 2;
                break;
            case 3:
                i = 1;
                break;
            }
                
            bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), i);
        }
    }
}

void Game::saveGame() {
    GameSnapshot snapshot(paletka, pilka, bloki);
    if (snapshot.saveToFile("zapis.txt")) {
        std::cout << "Gra zapisana!" << std::endl;
    }
    else {
        std::cout << "Blad zapisu gry!" << std::endl;
    }
}

void Game::loadGame() {
    GameSnapshot snapshot;
    if (snapshot.loadFromFile("zapis.txt")) {
        // Ustaw pozycjê paletki
        paletka.setPosition(snapshot.getPaddlePosition());

        // Ustaw pozycjê i prêdkoœæ pi³ki
        pilka.setPosition(snapshot.getBallPosition());
        pilka.setVelocity(snapshot.getBallVelocity());

        // Odtwórz bloki
        bloki.clear();
        const float ROZMIAR_BLOKU_X = (640.f - (12 - 1) * 2.f) / 12;
        const float ROZMIAR_BLOKU_Y = 20.f;

        for (const auto& blockData : snapshot.getBlocks()) {
            bloki.emplace_back(
                sf::Vector2f(blockData.x, blockData.y),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                blockData.hp
            );
        }

        currentScore = 0;
        currentState = GameState::Playing;
        std::cout << "Gra wczytana!" << std::endl;
    }
    else {
        std::cout << "Blad wczytywania gry! Plik nie istnieje." << std::endl;
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            // Obs³uga ESC - powrót do menu z gry
            if (event.key.code == sf::Keyboard::Escape && currentState == GameState::Playing || currentState == GameState::Scores) {
                currentScore = 0;
                currentState = GameState::Menu;
            }

            // ZAPIS GRY - F5
            if (event.key.code == sf::Keyboard::F5 && currentState == GameState::Playing) {
                saveGame();
            }

            // Obs³uga menu g³ównego
            if (currentState == GameState::Menu) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.myDelay(250);
                    menu.przesunG();
                }

                if (event.key.code == sf::Keyboard::Down) {
                    menu.myDelay(250);
                    menu.przesunD();
                }

                if (event.key.code == sf::Keyboard::Enter) {
                    switch (menu.getSelectedItem()) {
                    case 0: // Nowa gra
                        resetGame();
                        currentState = GameState::Playing;
                        std::cout << "Uruchamiam gre..." << std::endl;
                        break;
                    case 1: // Wczytaj Gre
                        loadGame();
                        currentState = GameState::Playing;
                        std::cout << "Wczytuje..." << std::endl;
                        break;
                    case 2: // Ostatnie wyniki
                        currentState = GameState::Scores;
                        std::cout << "Najlepsze wyniki..." << std::endl;
                        break;
                    case 3: // Wyjœcie
                        currentState = GameState::Exiting;
                        std::cout << "Koniec gry..." << std::endl;
                        break;
                    }
                }
            }
        }
    }
}

void Game::update(sf::Time dt) {
    // AKTUALIZUJ GRÊ TYLKO W STANIE PLAYING
    if (currentState != GameState::Playing) {
        return;
    }

    paletka.controlPaddle();
    pilka.controlBall();

    pilka.collidePaddle(paletka);
    
    currentScore += pilka.collideBricks(bloki);     //Funkcja odpowiedzialna za kolizjê pilki z blokami, która zwraca punkty

    // Sprawdzanie czy pi³ka wypad³a
    if (pilka.getPosition().y - pilka.getRadius() > 480.f || currentScore == 1920) {
        std::cout << "KONIEC GRY!" << std::endl;

        // ZAPISZ WYNIK PRZED POWROTEM DO MENU
        scoresManager.addScore(Name, currentScore);
        currentScore = 0; // Resetuj wynik
        currentState = GameState::Menu; // Powrót do menu po przegranej
    }
}

void Game::render() {
    window.clear(sf::Color(20, 20, 30));

    switch (currentState) {
    case GameState::Menu:
        menu.draw(window);
        break;
    case GameState::Playing:
        // RYSUJ TYLKO ELEMENTY GRY
        paletka.draw(window);
        pilka.draw(window);
        for (auto& blk : bloki) {
            blk.draw(window);
        }
        scoresManager.renderCurrentScore(window, currentScore);
        break;
    case GameState::Scores:
        scoresManager.renderScoresScreen(window);
    break;
    case GameState::Exiting:
        window.close();
        break;
    }

    window.display();
}

void Game::run() {

    sf::Clock clock;

    while (window.isOpen()) {

        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();

    }
}
#include "Game.hpp"

//Konstruktor
Game::Game()
    : window(sf::VideoMode(640.f, 480.f), "Arkanoid")
    , paletka(640.f / 2.f, 480.f - 30.f, 100.f, 20.f, 8.f)
    , pilka(640.f / 2.f, 200.f, 4.f, 3.f, 8.f)
    , menu(window.getSize().x, window.getSize().y)
    , currentState(GameState::Menu)
{
    float szerokoscOkna = 640.f;
    float wysokoscOkna = 480.f;

    window.setFramerateLimit(60);

    // Tworzenie bloków
    const int ILOSC_KOLUMN = 12;
    const int ILOSC_WIERSZY = 4;
    float ROZMIAR_BLOKU_X = (640.f - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 20.f;
    
    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
            bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), 3);
        }
    }
}

//metody

void Game::resetGame() {
    paletka = Paddle(640.f / 2.f, 480.f - 30.f, 100.f, 20.f, 8.f);
    pilka = Ball(640.f / 2.f, 200.f, 4.f, 3.f, 8.f);

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

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            // Obs³uga ESC - powrót do menu z gry
            if (event.key.code == sf::Keyboard::Escape && currentState == GameState::Playing) {
                currentState = GameState::Menu;
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
                    case 1: // Ostatnie wyniki
                        currentState = GameState::Scores;
                        std::cout << "Najlepsze wyniki..." << std::endl;
                        break;
                    case 2: // Wyjœcie
                        currentState = GameState::Exiting;
                        std::cout << "Koniec gry..." << std::endl;
                        break;
                    }
                }
            }

            // Obs³uga ekranu wyników
            if (currentState == GameState::Scores && event.key.code == sf::Keyboard::Escape) {
                currentState = GameState::Menu;
            }
        }
    }
}

void Game::controlPaddle() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        paletka.moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        paletka.moveRight();

    paletka.clampToBounds(640.f);
}

void Game::controlBall() {
    pilka.move();
    pilka.collideWalls(640.f, 480.f);
}

void Game::update(sf::Time dt) {
    // AKTUALIZUJ GRÊ TYLKO W STANIE PLAYING
    if (currentState != GameState::Playing) {
        return;
    }

    controlPaddle();
    controlBall();

    // Kolizja Pi³ka-Paletka
    sf::Vector2f ballPos = pilka.getPosition();
    sf::Vector2f paddlePos = paletka.getPosition();
    float paddleWidth = paletka.getWidth();
    float paddleHeight = paletka.getHeight();

    if (ballPos.x + pilka.getRadius() >= paddlePos.x - paddleWidth / 2.f &&
        ballPos.x - pilka.getRadius() <= paddlePos.x + paddleWidth / 2.f &&
        ballPos.y + pilka.getRadius() >= paddlePos.y - paddleHeight / 2.f) {
        if (ballPos.y < paddlePos.y)
            pilka.bounceY();
    }

    // Kolizja Pi³ka-Bloki
    for (auto& blk : bloki) {
        if (!blk.czyZniszczony()) {
            sf::FloatRect brickBounds = blk.getGlobalBounds();
            sf::FloatRect ballBounds(ballPos.x - pilka.getRadius(),
                ballPos.y - pilka.getRadius(),
                pilka.getRadius() * 2,
                pilka.getRadius() * 2);

            if (brickBounds.intersects(ballBounds)) {
                blk.trafienie();

                // Sprawdzenie kierunku kolizji
                float overlapLeft = ballBounds.left + ballBounds.width - brickBounds.left;
                float overlapRight = brickBounds.left + brickBounds.width - ballBounds.left;
                float overlapTop = ballBounds.top + ballBounds.height - brickBounds.top;
                float overlapBottom = brickBounds.top + brickBounds.height - ballBounds.top;

                bool fromLeft = overlapLeft < overlapRight;
                bool fromTop = overlapTop < overlapBottom;

                float minOverlapX = fromLeft ? overlapLeft : overlapRight;
                float minOverlapY = fromTop ? overlapTop : overlapBottom;

                if (minOverlapX < minOverlapY) {
                    pilka.bounceX();
                }
                else {
                    pilka.bounceY();
                }

                break;
            }
        }
    }

    // Sprawdzanie czy pi³ka wypad³a
    if (ballPos.y - pilka.getRadius() > 480.f) {
        std::cout << "KONIEC GRY!" << std::endl;
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
        break;
    case GameState::Scores:
        // Tymczasowe renderowanie ekranu wyników
    {
        sf::Font font;
        if (font.loadFromFile("arial.ttf")) {
            sf::Text text;
            text.setFont(font);
            text.setString("Ekran wynikow - Nacisnij ESC aby wrocic do menu");
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            text.setPosition(100, 300);
            window.draw(text);
        }
    }
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

        if (currentState == GameState::Exiting) {
            window.close();
            break;
        }

        update(deltaTime);
        render();
    }
}
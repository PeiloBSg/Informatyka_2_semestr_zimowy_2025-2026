#pragma once
#include <iostream>
#include "Pilka.h"
#include "Paletka.h"
#include "Cegla.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    Paddle paletka;
    Ball pilka;
    std::vector<Brick> bloki;

    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    void update() {
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

                    // Sprawdzenie z której strony nast¹pi³a kolizja
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
    }

    void render() {
        window.clear(sf::Color(20, 20, 30));
        paletka.draw(window);
        pilka.draw(window);

        for (auto& blk : bloki) {
            if (!blk.czyZniszczony()) {
                blk.draw(window);
            }
        }

        window.display();
    }

public:
    Game() : window(sf::VideoMode(WIDTH, HEIGHT), "Arkanoid"),
        paletka(WIDTH / 2.f, HEIGHT - 30.f, 100.f, 20.f, 8.f),
        pilka(WIDTH / 2.f, 200.f, 4.f, 3.f, 8.f) {

        window.setFramerateLimit(60);

        // Tworzenie bloków
        const int ILOSC_KOLUMN = 12;
        const int ILOSC_WIERSZY = 4;
        float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
        float ROZMIAR_BLOKU_Y = 20.f;

        for (int y = 0; y < ILOSC_WIERSZY; y++) {
            for (int x = 0; x < ILOSC_KOLUMN; x++) {
                float posX = x * (ROZMIAR_BLOKU_X + 2.f);
                float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
                bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), 3);
            }
        }
    }

    void run() {
        while (window.isOpen()) {
            processEvents();

            // Sterowanie paletk¹
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                paletka.moveLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                paletka.moveRight();

            paletka.clampToBounds(WIDTH);
            pilka.move();
            pilka.collideWalls(WIDTH, HEIGHT);

            update();

            // Sprawdzanie czy pi³ka wypad³a
            sf::Vector2f ballPos = pilka.getPosition();
            if (ballPos.y - pilka.getRadius() > HEIGHT) {
                std::cout << "KONIEC GRY!" << std::endl;
                window.close();
            }

            render();
        }
    }
};
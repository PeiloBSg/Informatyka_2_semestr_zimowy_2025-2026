#include <iostream>
#include "Pilka.hpp"
#include "Paletka.hpp"
#include "Cegla.hpp"
#include <SFML/Graphics.hpp>
#include <vector>


int main() {

    const float WIDTH = 640.f;      //640
    const float HEIGHT = 480.f;     //480

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Arkanoid");
    window.setFramerateLimit(60);

    //Tworzenie obiektów gry
    Paddle paletka(WIDTH / 2.f, HEIGHT - 30.f, 100.f, 20.f, 8.f); // x,y,szer,wys, predkosc 
    Ball pilka(WIDTH / 2.f, 200.f, 4.f, 3.f, 8.f); // x,y,vx,vy,radius

    //Tworzenie bloków brick 
    std::vector<Brick> bloki;       //bloki cegły

    //Ustalenie właściwości poziomu
    const int ILOSC_KOLUMN = 12;
    const int ILOSC_WIERSZY = 4;
    float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;      //Uzależnienie od szerokości ekranu
    float ROZMIAR_BLOKU_Y = 20.f;

    //Procedura rysująca bloki
    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);       //2px na przerwę
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;

            bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), 3);
        }
    }

    //Pętla Główna
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            paletka.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            paletka.moveRight();

        paletka.clampToBounds(WIDTH);
        pilka.move();
        pilka.collideWalls(WIDTH, HEIGHT);

        //Kolizja Piłka-Paletka
        sf::Vector2f ballPos = pilka.getPosition();
        sf::Vector2f paddlePos = paletka.getPosition();
        float paddleWidth = paletka.getWidth();
        float paddleHeight = paletka.getHeight();
        if (ballPos.x + pilka.getRadius() >= paddlePos.x - paddleWidth / 2.f &&
            ballPos.x - pilka.getRadius() <= paddlePos.x + paddleWidth / 2.f &&
            ballPos.y + pilka.getRadius() >= paddlePos.y - paddleHeight / 2.f) {
            if (ballPos.y < paddlePos.y) // Sprawdza cz piłka uderza od góry
                pilka.bounceY();
        }

        //Kolizja Piłka-Bloki
        for (auto& blk : bloki) {
            if (!blk.czyZniszczony()) {
                sf::FloatRect brickBounds = blk.getGlobalBounds();
                sf::FloatRect ballBounds(ballPos.x - pilka.getRadius(),
                    ballPos.y - pilka.getRadius(),
                    pilka.getRadius() * 2,
                    pilka.getRadius() * 2);

                if (brickBounds.intersects(ballBounds)) {
                    blk.trafienie();

                    // SPRAWDZENIE Z KTÓREJ STRONY NASTĄPIŁA KOLIZJA
                    float overlapLeft = ballBounds.left + ballBounds.width - brickBounds.left;
                    float overlapRight = brickBounds.left + brickBounds.width - ballBounds.left;
                    float overlapTop = ballBounds.top + ballBounds.height - brickBounds.top;
                    float overlapBottom = brickBounds.top + brickBounds.height - ballBounds.top;

                    // Znajdź najmniejszy overlap aby określić kierunek kolizji
                    bool fromLeft = overlapLeft < overlapRight;
                    bool fromTop = overlapTop < overlapBottom;

                    float minOverlapX = fromLeft ? overlapLeft : overlapRight;
                    float minOverlapY = fromTop ? overlapTop : overlapBottom;

                    if (minOverlapX < minOverlapY) {
                        // Kolizja pozioma (lewa/prawa strona)
                        pilka.bounceX();
                    }
                    else {
                        // Kolizja pionowa (góra/dół)
                        pilka.bounceY();
                    }

                    break; // Jedna kolizja na klatkę
                }
            }
        }

        // sprawdzanie czy pilka wypadla
        if (ballPos.y - pilka.getRadius() > HEIGHT) {
            std::cout << "KONIEC GRY!" << std::endl;
            window.close();
        }

        //Renderowanie
        window.clear(sf::Color(20, 20, 30));
        paletka.draw(window);
        pilka.draw(window);
        //rysowanie bloków
        for (auto& blk : bloki) {
            blk.draw(window);
        }
        window.display();
    }



    return 0;
}
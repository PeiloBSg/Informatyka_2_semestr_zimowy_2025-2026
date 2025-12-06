#include "Game.hpp"

//Konstruktor
Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid")
    , paletka(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 30.f, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED)
    , pilka(WINDOW_WIDTH / 2.f, 200.f, BALL_SPEED_X, BALL_SPEED_Y, BALL_RADIUS)
    , menu(window.getSize().x, window.getSize().y)
    , currentState(GameState::Menu)
    , currentScore(0)
    , Name("Pawel")
{
    window.setFramerateLimit(60);
    loadResources();
}

//Metody

void Game::loadResources() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Blad ladowania czcionki!" << std::endl;
    }
    scoresManager.setFont(font);
}

void Game::initBlocks() {
    bloki.clear();
    int hpPerRow[BLOCKS_ROWS] = { 3, 3, 2, 1 };

    for (int y = 0; y < BLOCKS_ROWS; y++) {
        for (int x = 0; x < BLOCKS_COLUMNS; x++) {
            float posX = x * (BLOCK_WIDTH + 2.f);
            float posY = y * (BLOCK_HEIGHT + 2.f) + 60.f;     
            bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT), hpPerRow[y]);
        }
    }
}

void Game::handleGameOver() {
    if (pilka.getPosition().y - pilka.getRadius() > WINDOW_HEIGHT || currentScore == MAX_SCORE) {
        std::cout << "KONIEC GRY!" << std::endl;
        scoresManager.addScore(Name, currentScore);
        currentScore = 0;
        currentState = GameState::Menu;
    }
}

void Game::handleGlobalKeys(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        // ESC - powrót do menu z gry lub wyników
        if (event.key.code == sf::Keyboard::Escape &&(currentState == GameState::Playing || currentState == GameState::Scores)) {
            currentScore = 0;
            currentState = GameState::Menu;
        }
        // ZAPIS GRY - F5
        if (event.key.code == sf::Keyboard::F5 && currentState == GameState::Playing) {
            snapshot.saveGame(paletka, pilka, bloki);
        }
    }
}

void Game::handleMenuInput(const sf::Event& event) {
    menu.handleMenuKeys(event);  // Strza³ki

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        switch (menu.getSelectedItem()) {
        case 0: // Nowa gra
            resetGame(); currentState = GameState::Playing; std::cout << "Uruchamiam gre..." << std::endl; break;
        case 1: // Wczytaj Gre
            snapshot.loadGame(paletka, pilka, bloki, BLOCK_WIDTH, BLOCK_HEIGHT); currentState = GameState::Playing; std::cout << "Wczytuje..." << std::endl; break;
        case 2: // Ostatnie wyniki
            currentState = GameState::Scores; std::cout << "Najlepsze wyniki..." << std::endl; break;
        case 3: // Wyjœcie
            currentState = GameState::Exiting; std::cout << "Koniec gry..." << std::endl; break;
        }
    }
}

void Game::resetGame() {
    paletka = Paddle(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 30.f, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED);
    pilka = Ball(WINDOW_WIDTH / 2.f, 200.f, BALL_SPEED_X, BALL_SPEED_Y, BALL_RADIUS);
    currentScore = 0;
    initBlocks();
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
 
            handleGlobalKeys(event);

            if (currentState == GameState::Menu) {      
                handleMenuInput(event);
            }
    }
}

void Game::update(sf::Time dt) {
    if (currentState != GameState::Playing) {   // AKTUALIZUJ GRÊ TYLKO W STANIE PLAYING
        return;
    }
    paletka.controlPaddle();
    pilka.controlBall();
    pilka.collidePaddle(paletka);
    currentScore += pilka.collideBricks(bloki);     //  Funkcja odpowiedzialna za kolizjê pilki z blokami, która zwraca zdobyte punkty
    handleGameOver();       // Sprawdzanie czy pi³ka wypad³a
}

void Game::render() {
    window.clear(sf::Color(20, 20, 30));

    switch (currentState) {
    case GameState::Menu:
        menu.draw(window);
        break;

    case GameState::Playing:
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
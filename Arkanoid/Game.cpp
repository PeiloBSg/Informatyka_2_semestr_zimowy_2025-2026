#include "Game.hpp"

//Konstruktor
Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid")
    , paletka(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - PADDLE_INIT_Y_OFFSET, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED)
    , pilka(WINDOW_WIDTH / 2.f, BALL_INIT_Y, BALL_SPEED_X, BALL_SPEED_Y, BALL_RADIUS)
    , bricks(BLOCK_WIDTH, BLOCK_HEIGHT, BLOCKS_ROWS, BLOCKS_COLUMNS, BLOCK_SPACING, BLOCK_OFFSET_Y)
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

void Game::resetGame() {
    paletka = Paddle(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 30.f, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED);
    pilka = Ball(WINDOW_WIDTH / 2.f, 200.f, BALL_SPEED_X, BALL_SPEED_Y, BALL_RADIUS);
    currentScore = 0;
    bricks.initBlocks(bloki);
}

void Game::returnToMenu() {
    currentScore = 0;
    currentState = GameState::Menu;
}

void Game::handleGameOver() {
    if (pilka.getPosition().y - pilka.getRadius() > WINDOW_HEIGHT || currentScore == MAX_SCORE) {
        std::cout << "KONIEC GRY!" << std::endl;
        scoresManager.addScore(Name, currentScore);
        returnToMenu();
    }
}

void Game::handleGlobalKeys(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        // ESC - powrót do menu z gry lub wyników
        if (event.key.code == sf::Keyboard::Escape && (currentState == GameState::Playing || currentState == GameState::Scores)) {
            returnToMenu();
        }
        // ZAPIS GRY - F5
        if (event.key.code == sf::Keyboard::F5 && currentState == GameState::Playing) {
            snapshot.saveGame(paletka, pilka, bloki);
        }
    }
}

void Game::handleMenuInput(const sf::Event& event) {
    menu.handleMenuKeys(event, dzwiek);   // Obs³uga strza³ek

    if (currentState == GameState::Menu && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        dzwiek.playSound(SoundType::MenuSelect);
        switch (menu.getSelectedItem()) {
        case 0: // Nowa gra
            resetGame(); 
            currentState = GameState::Playing; 
            std::cout << "Uruchamiam gre..." << std::endl; 
            break;
        case 1: // Wczytaj Gre
            currentScore = snapshot.loadGame(paletka, pilka, bloki, BLOCK_WIDTH, BLOCK_HEIGHT); 
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

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
            handleGlobalKeys(event);
            handleMenuInput(event);      
    }
}

void Game::update(sf::Time dt) {
    if (currentState != GameState::Playing) { return; }
    paletka.controlPaddle();
    pilka.controlBall(dzwiek);
    pilka.collidePaddle(paletka, dzwiek);
    currentScore += pilka.collideBricks(bloki, dzwiek);     // Funkcja odpowiedzialna za kolizjê pilki z blokami, która zwraca zdobyte punkty
    handleGameOver();                               // Sprawdzanie czy pi³ka wypad³a lub czy zniszczono wszystkie bloki
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
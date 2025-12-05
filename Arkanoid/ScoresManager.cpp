#include "ScoresManager.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

ScoresManager::ScoresManager() {
    loadScores();
}

void ScoresManager::setFont(sf::Font& font) {
    this->font = &font;
}

void ScoresManager::loadScores() {
    highScores.clear();
    std::ifstream file("scores.txt");
    if (!file.is_open()) return;

    HighScore score;
    long timestamp;

    while (file >> score.playerName >> score.score >> timestamp) {
        score.timestamp = timestamp;
        highScores.push_back(score);
    }

    // Sortowanie od najnowszego (najwiêkszy timestamp)
    std::sort(highScores.begin(), highScores.end());
    file.close();
}

void ScoresManager::saveScores() {
    std::ofstream file("scores.txt");
    for (const auto& score : highScores) {
        file << score.playerName << " " << score.score << " " << score.timestamp << "\n";
    }
    file.close();
}

void ScoresManager::addScore(const std::string& name, int score) {
    // Pobierz aktualny czas
    std::time_t currentTime = std::time(nullptr);

    HighScore newScore{ name, score, currentTime };
    highScores.push_back(newScore);

    // Sortowanie od najnowszego
    std::sort(highScores.begin(), highScores.end());

    // Zachowaj tylko ostatnie wyniki
    if (highScores.size() > MAX_SCORES) {
        highScores.resize(MAX_SCORES);
    }

    saveScores();
}

const std::vector<HighScore>& ScoresManager::getScores() const {
    return highScores;
}

void ScoresManager::clearScores() {
    highScores.clear();
    saveScores();
}

std::string ScoresManager::formatDate(std::time_t timestamp) const {
    // BEZPIECZNA WERSJA z localtime_s
    std::tm timeInfo = {};

#ifdef _WIN32
    // Dla Windows u¿ywamy localtime_s
    localtime_s(&timeInfo, &timestamp);
#else
    // Dla innych platform u¿ywamy localtime_r
    localtime_r(&timestamp, &timeInfo);
#endif

    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", &timeInfo);
    return std::string(buffer);
}

void ScoresManager::renderScoresScreen(sf::RenderWindow& window) {
    if (!font) return;  // Jeœli nie ma czcionki, nie renderuj

    // Tytu³
    sf::Text title;
    title.setFont(*font);
    title.setString("OSTATNIE WYNIKI");
    title.setCharacterSize(32);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(220, 30);
    window.draw(title);

    // Lista wyników
    if (highScores.empty()) {
        sf::Text noScores;
        noScores.setFont(*font);
        noScores.setString("Brak zapisanych wynikow");
        noScores.setCharacterSize(24);
        noScores.setFillColor(sf::Color::White);
        noScores.setPosition(200, 200);
        window.draw(noScores);
    }
    else {
        // Wyniki
        for (size_t i = 0; i < highScores.size() && i < 10; ++i) {
            std::string scoreLine =
                std::to_string(i + 1) + ". " +
                highScores[i].playerName + " - " +
                std::to_string(highScores[i].score) + " - " +
                formatDate(highScores[i].timestamp);

            sf::Text scoreText;
            scoreText.setFont(*font);
            scoreText.setString(scoreLine);
            scoreText.setCharacterSize(18);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(100, 100 + i * 30);
            window.draw(scoreText);
        }
    }

    // Instrukcja powrotu
    sf::Text instruction;
    instruction.setFont(*font);
    instruction.setString("Nacisnij ESC aby wrocic do menu");
    instruction.setCharacterSize(18);
    instruction.setFillColor(sf::Color::Cyan);
    instruction.setPosition(180, 400);
    window.draw(instruction);
}

void ScoresManager::renderCurrentScore(sf::RenderWindow& window, int currentScore) {
    if (!font) return;  // Jeœli nie ma czcionki, nie renderuj

    sf::Text scoreText;
    scoreText.setFont(*font);
    scoreText.setString("Wynik: " + std::to_string(currentScore));
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    window.draw(scoreText);
}
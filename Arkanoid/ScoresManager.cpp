#include "ScoresManager.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

ScoresManager::ScoresManager() {
    loadScores();
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
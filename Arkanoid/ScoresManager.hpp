#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

struct HighScore {
    std::string playerName;
    int score;
    std::time_t timestamp;

    bool operator<(const HighScore& other) const {
        return timestamp > other.timestamp;
    }
};

class ScoresManager {
private:
    std::vector<HighScore> highScores;
    const int MAX_SCORES = 10;

public:
    ScoresManager();
    void loadScores();
    void saveScores();
    void addScore(const std::string& name, int score);
    const std::vector<HighScore>& getScores() const;
    void clearScores();
    std::string formatDate(std::time_t timestamp) const;
};
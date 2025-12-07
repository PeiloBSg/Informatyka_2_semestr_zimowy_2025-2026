#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <SFML/Graphics.hpp>

struct HighScore {
    std::string playerName;         // Imiê gracza
    int score;                      // Wynika gracza
    std::time_t timestamp;          // Czas 
                                                            
    bool operator<(const HighScore& other) const {      
        return timestamp > other.timestamp;
    }
};

class ScoresManager {
private:
    std::vector<HighScore> highScores;      // Wynik
    const int MAX_SCORES = 10;              // Maksywalna liczba wyœwietlanych wyników
    sf::Font* font = nullptr;               // WskaŸnik do czcionki

public:
    ScoresManager();

    //Metody
    void setFont(sf::Font& font);                                               // Setter czcionki
    void loadScores();                                                          // Wczytuje wyniki
    void saveScores();                                                          // Zapisuje wyniki
    void addScore(const std::string& name, int score);                          // Dodaje wynik
    const std::vector<HighScore>& getScores() const;                            // Poniera wyniki wraz z dat¹
    void clearScores();                                                         // Czyœci wyniki
    std::string formatDate(std::time_t timestamp) const;                        // Format daty
    void renderScoresScreen(sf::RenderWindow& window);                          // Renderuje okno z wynikami
    void renderCurrentScore(sf::RenderWindow& window, int currentScore);        // Wyœwietla aktualny wynik na ekranie

};
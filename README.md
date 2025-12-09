## Autor
- Paweł Rogula
- Politechnika Gdańska
- Nr indeksu: 203988 
- Projekt: Gra Arkanoid

## Opis
Klasyczna gra Arkanoid zbudowana w C++ z użyciem biblioteki SFML. Gra zawiera system zapisywania stanu gry, tabelę wyników oraz różne poziomy życia bloków.

## Instrukcja Pobrania
Wszystkie pliki znajdują się w folderze Arkanoid

## Wymagania
- Kompilator C++
- Biblioteka SFML 2.5.1

## Sterowanie
- **Menu główne**: strzałki góra/dół + ENTER
- **Sterowanie paletką**: A/D lub strzałki lewo/prawo
- **Zapis gry**: F5
- **Powrót do menu**: ESC

## Funkcjonalności
- Zapis i wczytywanie stanu gry
- System najlepszych wyników
- Różne poziomy wytrzymałości bloków
- Kolizje piłki z paletką i blokami
- Menu z opcjami: Nowa gra, Wczytaj grę, Wyniki, Wyjście

## Struktura projektu
- `Arkanoid.cpp` - main
- `Game.hpp/cpp` - główna klasa gry
- `Pilka.hpp/cpp` - logika piłki
- `Paletka.hpp/cpp` - logika paletki
- `Cegla.hpp/cpp` - logika bloku
- `Cegly.hpp/cpp` - tworzenie bloków
- `Menu.hpp/cpp` - system menu
- `GameSnapshot.hpp/cpp` - zapis/odczyt stanu gry
- `ScoresManager.hpp/cpp` - zarządzanie wynikami
- `StanGry.hpp` - enum stanów gry
- `arial.ttf` - czcionka
- `zapis.txt` - plik zapisu gry
- `scores.txt` - plik z wynikami       
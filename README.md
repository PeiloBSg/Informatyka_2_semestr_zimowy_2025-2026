## Autor
- Paweł Rogula
- Politechnika Gdańska
- Nr indeksu: 203988 
- Projekt: Gra Arkanoid

## Opis
Klasyczna gra Arkanoid zbudowana w C++ z użyciem biblioteki SFML. Gra zawiera system zapisywania stanu gry, tabelę wyników, różne poziomy życia bloków oraz dźwięki.

## Instrukcja Pobrania
Wszystkie pliki znajdują się w folderze Arkanoid

## Wymagania

### Wymagania systemowe:
- Kompilator C++
- Biblioteka SFML 2.6.2
### Konfiguracja projektu (Visual Studio):
Wejdź w właściowści projektu, a następnie: 
#### 1. W sekcji katalogi VC ++:
- Dodaj ścieżkę do folderu /include z pobranej bibiloteki SFML dla katalowgów nagłówkowych
- Dodaj ścieżkę do folderu /lib z pobranej bibiloteki SFML dla katalowgów bibliotek
#### 2. W sekcji C++ -> Preprocesor:
- Dodaj definicję preprocesora: SFML_STATIC
#### 3. W sekcji Konsolidator -> Dane Wejściowe:
- Dodaj dodatkowe zależności: sfml-window-s.lib;sfml-audio.lib;sfml-system-s.lib;sfml-graphics-s.lib;opengl32.lib;freetype.lib;winmm.lib;gdi32.lib;
#### 4. Do folderu projektu -> x64 -> Release:
- Przekopiuj wszystkie pliki z folderu SFML-2.6.2 -> bin

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
- Dźwięki poszczególnych czynności 

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
- `Dzwieki.hpp/cpp` - zarządzanie dźwiękami
- `StanGry.hpp` - enum stanów gry
- `StanDzwieku.hpp` - enum stanów dźwięków
- `arial.ttf` - czcionka
- `zapis.txt` - plik zapisu gry
- `scores.txt` - plik z wynikami
- `bounce.wav` - dźwięk odbicia piłki
- `hit.wav` - dźwięk trafienia piłki w blok
- `menuarrow.wav` - dźwięk przełączania opcji w menu
- `menuselect.wav` - dźwięk wybru opcji w menu
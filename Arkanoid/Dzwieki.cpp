#include "Dzwieki.hpp"

//Konstruktor
Sounds::Sounds() {
	loadSounds();
}

//Metody
void Sounds::loadSounds() {
    loadBounce();
    loadHit();
    loadMenuArrow();
    loadMenuSelect();
}

void Sounds::loadBounce() {
    if (soundOdbicie.loadFromFile("bounce.wav")) {
        odbicie.setBuffer(soundOdbicie);
        odbicie.setVolume(30.0f);
    }
    else {
        std::cout << "Nie znaleziono pliku bounce.wav" << std::endl;
    }
}

void Sounds::loadHit() {
    if (soundTrafienie.loadFromFile("hit.wav")) {
        trafienie.setBuffer(soundTrafienie);
        trafienie.setVolume(30.0f);
    }
    else {
        std::cout << "Nie znaleziono pliku hit.wav" << std::endl;
    }
}

void Sounds::loadMenuArrow() {
    if (soundPrzesuwanie.loadFromFile("menuarrow.wav")) {
        przesuwanie.setBuffer(soundPrzesuwanie);
        przesuwanie.setVolume(30.0f);
    }
    else {
        std::cout << "Nie znaleziono pliku menuarrow.wav" << std::endl;
    }
}

void Sounds::loadMenuSelect() {
    if (soundWybieranie.loadFromFile("menuselect.wav")) {
        wybieranie.setBuffer(soundWybieranie);
        wybieranie.setVolume(30.0f);
    }
    else {
        std::cout << "Nie znaleziono pliku menuselect.wav" << std::endl;
    }
}

void Sounds::playSound(SoundType currentSound) {
    switch (currentSound) {
    case SoundType::Bounce:
        if (odbicie.getBuffer() != nullptr) {
            odbicie.play();
        }
        break;
    case SoundType::Hit:
        if (trafienie.getBuffer() != nullptr) {
            trafienie.play();
        }
        break;
    case SoundType::MenuArrow:
        if (przesuwanie.getBuffer() != nullptr) {
            przesuwanie.play();
        }
        break;
    case SoundType::MenuSelect:
        if (wybieranie.getBuffer() != nullptr) {
            wybieranie.play();
        }
        break;
    }
    

}

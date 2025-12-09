#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include "StanDzwieku.hpp"

class Sounds {
private:
	//SoundType currentSound;
	sf::SoundBuffer soundOdbicie;			// Buffer dŸwiêku odbicia
	sf::SoundBuffer soundTrafienie;			// Buffer dŸwiêku trafienia
	sf::SoundBuffer soundPrzesuwanie;		// Buffer dŸwiêku przesuwania
	sf::SoundBuffer soundWybieranie;		// Buffer dŸwiêku wybierania
	sf::Sound odbicie;						// DŸwiêk odbicia sie pi³ki
	sf::Sound trafienie;					// DŸwiêk trafienia bloku
	sf::Sound przesuwanie;					// D¿wiêk przesuwania strza³ek w menu
	sf::Sound wybieranie;					// DŸwiêk wybierania w menu
	void loadSounds();						// Wczytuje wszystkie dŸwiêki
	void loadBounce();						// Wczytuje dŸwiêk odbicia
	void loadHit();							// Wczytuje dŸwiêk trafienia
	void loadMenuArrow();					// Wczytuje dŸwiêk przesuwania strza³kami w menu
	void loadMenuSelect();					// Wczytuje dŸwiêk wyboru w menu

public:
	Sounds();
	void playSound(SoundType currnetSound);			// Metoda odtwarzajaca dany dŸwiêk

};
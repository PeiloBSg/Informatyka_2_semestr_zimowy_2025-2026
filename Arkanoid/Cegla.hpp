#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array> //prosta tablica stalego rozmiaru

class Brick : public sf::RectangleShape {
private:
	int punktyZycia;	// 0-3
	bool jestZniszczony;		// Jeœli zniszczony to =true
	static const std::array<sf::Color, 4> colorLUT;			// Tablica Look-up

public:
	Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L);

	//Metody
	void aktualizujKolor();		// Funkcja zmieniania kolor klocka w zale¿noœci od punktyZycia
	void trafienie();		// Mechanizm aktualizacji punktów ¿ycia
	void draw(sf::RenderTarget& window);

	//Getter
	bool czyZniszczony() const;
	sf::Vector2f getPosition() const;
	int getHP() const;

};
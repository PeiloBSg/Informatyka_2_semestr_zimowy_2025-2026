#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

class Brick : public sf::RectangleShape {
private:
	int punktyZycia;										// 0-3
	bool jestZniszczony;									// Jeœli zniszczony to =true
	static const std::array<sf::Color, 4> colorLUT;			// Tablica look-up

public:
	Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L);

	//Metody
	void aktualizujKolor();						// Funkcja zmieniania kolor klocka w zale¿noœci od punktyZycia
	void trafienie();							// Mechanizm aktualizacji punktów ¿ycia
	void draw(sf::RenderTarget& window);		// Rysuje bloki

	//Gettey
	bool czyZniszczony() const;					// Zwraca, czy blok jest zniszczony 
	sf::Vector2f getPosition() const;			// Zwraca pozycjê bloku
	int getHP() const;							// Zwraca ¿ycie bloku

};
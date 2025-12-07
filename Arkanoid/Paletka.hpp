#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Paddle {
private:
	sf::Vector2f Pozycja;			// Pozycja paletki
	float V;						// Prêdkoœæ X paletki 
	float d;						// D³ugoœæ paletki
	float h;						// Wysokoœæ paletki
	sf::RectangleShape shape;		// Tworzy prostok¹tny kszta³t

public:
	Paddle(float sx, float sy, float sd, float sh, float sV);

	//Metody
	void moveLeft();									// Przesuwa paletkê w lewo
	void moveRight();									// Przesuwa paletkê w prawo
	void clampToBounds(float width);					// Fizyka kolizji z bocznymi œciankami ekranu
	void draw(sf::RenderTarget& target);				// Rysuje paletkê
	void setPosition(const sf::Vector2f& position);		// Ustawia pozycjê paletki
	void controlPaddle();								// Sterowanie paletk¹

	//Gettery
	sf::Vector2f getPosition() const;			// Zwraca pozycjê paletki
	float getHeight() const;					// Zwraca wysokoœæ paletki
	float getWidth() const;						// Zwraca szerokoœæ paletki

};
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Paddle {
private:
	sf::Vector2f Pozycja;
	float V;		//Prêdkoœæ Paletki
	float d;		//D³ugoœæ Paletki
	float h;		//Wysokoœæ Paletki
	sf::RectangleShape shape;

public:
	Paddle(float sx, float sy, float sd, float sh, float sV);

	void moveLeft();
	void moveRight();
	void clampToBounds(float width);
	void draw(sf::RenderTarget& target);

	//Gettery
	sf::Vector2f getPosition() const;
	float getHeight() const;
	float getWidth() const;

};
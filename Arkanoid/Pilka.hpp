#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paletka.hpp"
#include "Cegla.hpp"

class Ball {
private:
	sf::Vector2f Pozycja;	//Pozycja Pi³ki
	sf::Vector2f VV;		//Prêdkoœæ Pi³ki
	float r;		//Promieñ Pi³ki
	sf::CircleShape shape;		//Kszta³t Pi³ki

public:
	Ball(float sx, float sy, float svx, float svy, float sr);

	//Metody
	void move();
	void bounceX();
	void bounceY();
	void collideWalls(float width, float height);
	void draw(sf::RenderTarget& target);
	void setPosition(const sf::Vector2f& position);
	void setVelocity(const sf::Vector2f& velocity);
	void controlBall();								//Sterowanie Pilk¹
	void collidePaddle(const Paddle& paddle);		//Kolizja Pilka-Palekta
	int collideBricks(std::vector<Brick>& bricks);	//Kolizja Pilka-Cegly, zwraca iloœæ zdobytych punktów

	//Gettery
	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	float getRadius() const;
};
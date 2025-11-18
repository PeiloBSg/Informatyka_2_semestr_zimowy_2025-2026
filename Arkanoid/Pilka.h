#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Ball {
private:
	sf::Vector2f Pozycja;	//Pozycja Pi³ki
	sf::Vector2f VV;		//Prêdkoœæ Pi³ki
	float r;		//Promieñ Pi³ki
	sf::CircleShape shape;		//Kszta³t Pi³ki

public:
	Ball(float sx, float sy, float svx, float svy, float sr) {
		Pozycja.x = sx;
		Pozycja.y = sy;
		VV.x = svx;
		VV.y = svy;
		r = sr;
		shape.setRadius(r);
		shape.setOrigin(r, r);
		shape.setPosition(Pozycja.x, Pozycja.y);
		shape.setFillColor(sf::Color::White);
	};
	void move();
	void bounceX();
	void bounceY();
	void collideWalls(float width, float height);
	void collidePaddle();
	void draw(sf::RenderTarget& target);

	//Gettery
	sf::Vector2f getPosition() const { return Pozycja; }
	sf::Vector2f getVelocity() const { return VV; }
	float getRadius() const { return r; }
};

void Ball::move() {
	Pozycja.x += VV.x;
	Pozycja.y += VV.y;
}

void Ball::bounceX() {
	VV.x = -VV.x;
}

void Ball::bounceY() {
	VV.y = -VV.y;
}

void Ball::collideWalls(float width, float height) {
	if (Pozycja.x - r <= 0 || Pozycja.x + r >= width)
		bounceX();
	if (Pozycja.y - r <= 0)
		bounceY();
}

void Ball::collidePaddle() {

}

void Ball::draw(sf::RenderTarget& target) {
	shape.setPosition(Pozycja);
	target.draw(shape);
}

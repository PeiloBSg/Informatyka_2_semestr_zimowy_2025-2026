#include "Pilka.hpp"


//Konstruktor
Ball::Ball(float sx, float sy, float svx, float svy, float sr) {
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

//Metody
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

//Gettery
sf::Vector2f Ball::getPosition() const { 
	return Pozycja; 
}

sf::Vector2f Ball::getVelocity() const { 
	return VV; 
}

float Ball::getRadius() const { 
	return r; 
}
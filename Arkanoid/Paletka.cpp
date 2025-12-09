#include "Paletka.hpp"

//Konstruktor
Paddle::Paddle(float sx, float sy, float sd, float sh, float sV) {
	Pozycja.x = sx;
	Pozycja.y = sy;
	d = sd;
	h = sh;
	V = sV;
	shape.setSize({ d, h });
	shape.setOrigin(d / 2, h / 2);
	shape.setPosition(Pozycja.x, Pozycja.y);
	shape.setFillColor(sf::Color(236, 73, 60));
}

//Metody
void Paddle::moveLeft() {
	Pozycja.x -= V;
}

void Paddle::moveRight() {
	Pozycja.x += V;
}

void Paddle::clampToBounds(float width) {
	if (Pozycja.x - d / 2 <= 0)
		Pozycja.x = d / 2;
	if (Pozycja.x + d / 2 >= width)
		Pozycja.x = width - d / 2;
}

void Paddle::draw(sf::RenderTarget& target) {
	shape.setPosition(Pozycja);
	target.draw(shape);
}

void Paddle::setPosition(const sf::Vector2f& position) {
	Pozycja = position;
}

void Paddle::controlPaddle() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveRight();

	clampToBounds(640.f);
}


//Gettery
sf::Vector2f Paddle::getPosition() const{
	return Pozycja;
}

float Paddle::getHeight() const { 
	return h; 
}

float Paddle::getWidth() const { 
	return d; 
}
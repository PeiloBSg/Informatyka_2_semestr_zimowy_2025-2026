#include "Cegla.hpp"

//Konstruktor
Brick::Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L) {
	if (L > 3)
		L = 3;
	if (L < 0)
		L = 0;
	punktyZycia = L;
	jestZniszczony = false;
	this->setFillColor(sf::Color::Yellow);
	this->setPosition(startPo);
	this->setSize(rozmiar);
	this->setOutlineColor(sf::Color::White);
	//this->setOutlineThickness(1.f);
	aktualizujKolor();
};

//Metody
const std::array<sf::Color, 4> Brick::colorLUT = {
	sf::Color::Transparent,			// Invisible
	sf::Color::Red ,				// Red
	sf::Color::Yellow,				// Yellow
	sf::Color(118, 255, 112)		// Green
};

void Brick::trafienie() {
	if (jestZniszczony == true)
		return;
	punktyZycia--;
	aktualizujKolor();
	if (punktyZycia <= 0)
		jestZniszczony = true;
}

void Brick::aktualizujKolor() {
	if (punktyZycia >= 0 && punktyZycia <= 3)
		this->setFillColor(colorLUT[punktyZycia]);
}

void Brick::draw(sf::RenderTarget& window) {
	if (!jestZniszczony) {  // Rysuj tylko jeœli nie zniszczony
		window.draw(*this);
	}
}

//Gettey
bool Brick::czyZniszczony() const {
	return jestZniszczony;
}

sf::Vector2f Brick::getPosition() const {
	return sf::RectangleShape::getPosition();
}

int Brick::getHP() const {
	return punktyZycia;
}
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
	sf::Color::Transparent,
	sf::Color::Red ,		//Yellow
	sf::Color::Yellow,		//Magenta
	sf::Color(118, 255, 112)		//Red
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
	if (!jestZniszczony) {  //Rysuj tylko jeœli nie zniszczony
		window.draw(*this);
	}
}
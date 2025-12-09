#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paletka.hpp"
#include "Cegla.hpp"
#include "Dzwieki.hpp"
#include "StanDzwieku.hpp"

class Ball {
private:	
	sf::Vector2f Pozycja;		// Pozycja pi³ki
	sf::Vector2f VV;			// Prêdkoœæ pi³ki
	float r;					// Promieñ pi³ki
	sf::CircleShape shape;		// Kszta³t pi³ki
	SoundType currentSound;		// DŸwiêk, który ma byæ puszczony

public:
	Ball(float sx, float sy, float svx, float svy, float sr);

	//Metody
	void move();														// Sprawia, ¿e pi³ka przesuwa siê o prêdkoœæ
	void bounceX();														// Obicie w p³a¿czyŸnie X
	void bounceY();														// Obicie w p³a¿czyŸnie Y
	void collideWalls(float width, float height, Sounds& sound);		// Kolizja ze œcianami okna
	void draw(sf::RenderTarget& target);								// Rysowanie pi³ki
	void setPosition(const sf::Vector2f& position);						// Ustawia pozycjê pi³ki
	void setVelocity(const sf::Vector2f& velocity);						// Ustawia prêdkoœæ pi³ki
	void controlBall(Sounds& sound);									// Sterowanie pilk¹
	void collidePaddle(const Paddle& paddle, Sounds& sound);			// Kolizja pilka-palekta
	int collideBricks(std::vector<Brick>& bricks, Sounds& sound);		// Kolizja pilka-cegly, zwraca iloœæ zdobytych punktów

	//Gettery
	sf::Vector2f getPosition() const;		// Zwraca pozycjê pi³ki
	sf::Vector2f getVelocity() const;		// Zwraca prêdkoœæ pi³ki
	float getRadius() const;				// Zwraca pronieñ pi³ki

};
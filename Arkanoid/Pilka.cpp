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
	currentSound = SoundType::Bounce;
}

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

void Ball::collideWalls(float width, float height, Sounds& sound) {
	if (Pozycja.x - r <= 0 || Pozycja.x + r >= width) {
		bounceX();
		currentSound = SoundType::Bounce;
		sound.playSound(currentSound);
	}
		
	if (Pozycja.y - r <= 0) {
		bounceY();
		currentSound = SoundType::Bounce;
		sound.playSound(currentSound);
	}
		
}

void Ball::draw(sf::RenderTarget& target) {
	shape.setPosition(Pozycja);
	target.draw(shape);
}

void Ball::setPosition(const sf::Vector2f& position) {
	Pozycja = position;
}

void Ball::setVelocity(const sf::Vector2f& velocity) {
	VV = velocity;
}

void Ball::controlBall(Sounds& sound) {
	move();
	collideWalls(640.f, 480.f, sound);
}

void Ball::collidePaddle(const Paddle& paddle, Sounds& sound) {
	sf::Vector2f paddlePos = paddle.getPosition();
	float paddleWidth = paddle.getWidth();
	float paddleHeight = paddle.getHeight();

	// Sprawdzenie kolizji
	if (Pozycja.x + r >= paddlePos.x - paddleWidth / 2.f &&
		Pozycja.x - r <= paddlePos.x + paddleWidth / 2.f &&
		Pozycja.y + r >= paddlePos.y - paddleHeight / 2.f) {

		// Upewnij siê, ¿e pi³ka jest nad paletk¹
		if (Pozycja.y < paddlePos.y) {
			bounceY();
			currentSound = SoundType::Bounce;
			sound.playSound(currentSound);
		}
	}
}

int Ball::collideBricks(std::vector<Brick>& bricks, Sounds& sound) {
	int pointsEarned = 0;
	sf::Vector2f ballPos = Pozycja;

	for (auto& brick : bricks) {
		if (!brick.czyZniszczony()) {
			sf::FloatRect brickBounds = brick.getGlobalBounds();
			sf::FloatRect ballBounds(ballPos.x - r,
				ballPos.y - r,
				r * 2,
				r * 2);

			if (brickBounds.intersects(ballBounds)) {
				brick.trafienie();

				// Punkty za zniszczenie bloku
				int brickPoints = (brick.getHP() + 1) * 10;
				pointsEarned += brickPoints;

				// Sprawdzenie kierunku kolizji
				float overlapLeft = ballBounds.left + ballBounds.width - brickBounds.left;
				float overlapRight = brickBounds.left + brickBounds.width - ballBounds.left;
				float overlapTop = ballBounds.top + ballBounds.height - brickBounds.top;
				float overlapBottom = brickBounds.top + brickBounds.height - ballBounds.top;

				bool fromLeft = overlapLeft < overlapRight;
				bool fromTop = overlapTop < overlapBottom;

				float minOverlapX = fromLeft ? overlapLeft : overlapRight;
				float minOverlapY = fromTop ? overlapTop : overlapBottom;

				if (minOverlapX < minOverlapY) {
					bounceX();
					currentSound = SoundType::Hit;
					sound.playSound(currentSound);
				}
				else {
					bounceY();
					currentSound = SoundType::Hit;
					sound.playSound(currentSound);
				}

				break; // Po kolizji z jednym blokiem przerywamy
			}
		}
	}

	return pointsEarned;
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
#include "Cegly.hpp"

//Konstruktor
Bricks::Bricks(float wymiarX, float wymiarY, int w, int k, float odst, float ofs) {
	WymiaryBloku.x = wymiarX;
	WymiaryBloku.y = wymiarY;
	wiersze = w;
	kolumny = k;
	odstepy = odst;
	offsetY = ofs;
};

//Metody
void Bricks::initBlocks(std::vector<Brick>& bricks) {
    bricks.clear();

    int hpPerRow[WIERSZE] = { 3, 3, 2, 1 };

    for (int y = 0; y < wiersze; y++) {
        for (int x = 0; x < kolumny; x++) {
            float posX = x * (WymiaryBloku.x + odstepy);
            float posY = y * (WymiaryBloku.y + odstepy) + offsetY;
            sf::Vector2f position(posX, posY);
            sf::Vector2f size(WymiaryBloku.x, WymiaryBloku.y);
            bricks.emplace_back(position, size, hpPerRow[y]);
        }
    }
};
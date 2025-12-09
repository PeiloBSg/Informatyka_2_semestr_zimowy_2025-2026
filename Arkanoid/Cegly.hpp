#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cegla.hpp"

class Bricks {
private:
    //Sta³e
    static const int WIERSZE = 4;   //Sta³a, tóra przechowuje iloœc wierszów
    
    sf::Vector2f WymiaryBloku;      // Wymiary jednego bloku
    int wiersze;                    // Iloœæ wierszy
    int kolumny;                    // Iloœæ kolumn
    float odstepy;                  // Odstêpy miêdzy blokami
    float offsetY;                  // Odstêp bloków od góry ekranu

public:
	Bricks(float wymiarX, float wymiarY, int w, int k, float odst, float ofs);

    //Metody
    void initBlocks(std::vector<Brick>& bricks);        // Metoda wdra¿aj¹ca bloki do gry, która usuwa wszystko, a nastêpnie tworzy nowe bloki

};
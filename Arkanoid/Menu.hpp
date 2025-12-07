#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_LICZBA_POZIOMOW 4

class Menu
{
private:
	sf::Font font;							// Czcionka
	sf::Text menu[MAX_LICZBA_POZIOMOW];		// Maksymalna liczba poziomow (czyli wierszy tekstu w menu)
	int selectedItem = 0;					// Wybrana opcja 

public:
	Menu(float width, float height);

	//Metody
	void przesunG();									// Przesun do gory
	void przesunD();									// Przesun w dol
	int getSelectedItem() { return selectedItem; }		// Zwroc poziom menu
	void draw(sf::RenderWindow &window);				// Rysuj menu w oknie
	void myDelay(int opoznienie);						// OpóŸnienie
	void handleMenuKeys(const sf::Event& event);		// Sterowanie w menu

};
#include "Menu.hpp"


//Konstruktor
Menu::Menu(float width, float height)
{	//laduj czcionke
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}
	//rysowanie elementow menu
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Nowa gra");
	menu[0].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Wczytaj gre");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Ostatnie wyniki");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Wyjscie");
	menu[3].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 4));
	currentSound = SoundType::MenuArrow;
}

//Metody
void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window.draw(menu[i]);
	}
}


void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}


}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}

}

//funklcja opozniajaca
void Menu::myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}

	}
}

void Menu::handleMenuKeys(const sf::Event& event, Sounds& sound) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up) {
			myDelay(250);
			przesunG();
			sound.playSound(currentSound);
		}

		if (event.key.code == sf::Keyboard::Down) {
			myDelay(250);
			przesunD();
			sound.playSound(currentSound);
		}
	}
}
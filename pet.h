#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class pet
{
private:
	sf::Texture tekstura;
	sf::RectangleShape ptak_ksztalt;
	sf::Clock zegar;
	bool czy_spacja_kliknieta = false;
	bool czy_zyje = true;
public:
	pet();
	sf::RectangleShape* ptak_ksztalt_return() { return &ptak_ksztalt; }
	void ustaw_czy_zyje(bool czy_zyje);
	void rysuj_pet(sf::RenderWindow* adres_okna);
	void sterowanie();
};


#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class pet
{
private:
	sf::Texture tekstura;
	sf::RectangleShape ptak_ksztalt;
public:
	pet();
	sf::RectangleShape* ptak_ksztalt_return() { return &ptak_ksztalt; }
	void rysuj_pet(sf::RenderWindow* adres_okna);
};


#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "pet.h"

class gra
{
public:
	gra(sf::RenderWindow *adres_okna);
	void draw();
private:
	pet ptak;
	sf::RenderWindow *adres_okna;
};

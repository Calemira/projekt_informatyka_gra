#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "pet.h"
#include "slupki.h"


class gra
{
public:
	gra(sf::RenderWindow *adres_okna, sf::View* adres_kamery);
	void draw();
	void sterowanie();
	void pozycja_kamery();
	void silnikfizyczny();
private:
	pet ptak;
	sf::RenderWindow *adres_okna;
	sf::RectangleShape oknogra;
	sf::Texture* teksturaa = new sf::Texture;
	sf::View* kamera;
	std::vector<slupki> slupki;
};

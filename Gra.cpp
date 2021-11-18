#include "Gra.h"
#include <SFML/Graphics.hpp>
#include <iostream>
gra::gra(sf::RenderWindow *adres_okna)
{
	this->adres_okna = adres_okna;
	ptak.ptak_ksztalt_return()->setPosition({ 10, 10 });
}
void gra::draw()
{
	ptak.rysuj_pet(adres_okna);
}
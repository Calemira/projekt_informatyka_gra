#include "pet.h"
#include <SFML/Graphics.hpp>
#include <iostream>

pet::pet()
{
	tekstura.loadFromFile("pet.png");
	ptak_ksztalt.setTexture(&tekstura);
	ptak_ksztalt.setSize({ 171,132 });
}
void pet::rysuj_pet(sf::RenderWindow *adres_okna)
{
	adres_okna->draw(ptak_ksztalt);
}

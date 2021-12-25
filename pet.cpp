#include "pet.h"
#include <SFML/Graphics.hpp>
#include <iostream>

pet::pet()
{
	tekstura.loadFromFile("pet.png");
	ptak_ksztalt.setTexture(&tekstura);
	ptak_ksztalt.setSize({ 76,46 });
}
void pet::rysuj_pet(sf::RenderWindow *adres_okna)
{
	adres_okna->draw(ptak_ksztalt);
}
void pet::sterowanie()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (czy_spacja_kliknieta == false)
		{
			czy_spacja_kliknieta = true;
			zegar.restart();
			ptak_ksztalt.setPosition(ptak_ksztalt.getPosition().x, ptak_ksztalt.getPosition().y-5);
		}
	}
	else
	{
		czy_spacja_kliknieta = false;
	}
	ptak_ksztalt.setPosition(ptak_ksztalt.getPosition().x + 4, ptak_ksztalt.getPosition().y - 5 + 10 * zegar.getElapsedTime().asSeconds());

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//{
	//	ptak_ksztalt.setPosition(ptak_ksztalt.getPosition().x+10, ptak_ksztalt.getPosition().y);//na potrzeby testow
	//}
}
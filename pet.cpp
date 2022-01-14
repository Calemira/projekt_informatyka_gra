#include "pet.h"
#include <SFML/Graphics.hpp>
#include <iostream>

pet::pet()
{
	tekstura.loadFromFile("pet.png");
	ptak_ksztalt.setTexture(&tekstura);
	ptak_ksztalt.setSize({ 76,46 });
	ptak_animacja = { &tekstura,2 };
	ptak_ksztalt.setTextureRect(ptak_animacja.klatka_zwroc());
}

void pet::rysuj_pet(sf::RenderWindow *adres_okna)
{
	adres_okna->draw(ptak_ksztalt);
	ptak_animacja.aktualizacja(int(czy_spacja_kliknieta));
	ptak_ksztalt.setTextureRect(ptak_animacja.klatka_zwroc());
}
void pet::sterowanie()
{
	zegar += 1.0 / 60.0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (czy_spacja_kliknieta == false)
		{
			czy_spacja_kliknieta = true;
			zegar = 0.0;
			ptak_ksztalt.setPosition(ptak_ksztalt.getPosition().x, ptak_ksztalt.getPosition().y-5);
		}
	}
	else
	{
		czy_spacja_kliknieta = false;
	}
	ptak_ksztalt.setPosition(ptak_ksztalt.getPosition().x + predkosc, ptak_ksztalt.getPosition().y - 3 + 10 * zegar);

}

void pet::ustaw_czy_zyje(bool czy_zyje)
{
	this->czy_zyje = czy_zyje;
}

void pet::ustaw_predkosc(float predkosc)
{
	this->predkosc = predkosc;
}
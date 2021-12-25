#include "Gra.h"
#include <SFML/Graphics.hpp>
#include <iostream>
gra::gra(sf::RenderWindow *adres_okna, sf::View* adres_kamery)
{
	srand(time(NULL));
	kamera = adres_kamery;
	oknogra.setPosition(0, 0);
	oknogra.setSize({ 800,600 });
	teksturaa->loadFromFile("tlo.png");
	oknogra.setTexture(teksturaa);
	this->adres_okna = adres_okna;
	ptak.ptak_ksztalt_return()->setPosition({ 70, 256 });
	for (int i=0;i<100;i++)
	{
		int x;
		x = -100 + rand() % 200;
		slupki.emplace_back(337.f+i*260.f, 0.f, 182.f+x);
		slupki.emplace_back(337.f+i*260.f, 352.f+x, 248.f-x);
	}

}
void gra::draw()
{
	adres_okna->draw(oknogra);
	ptak.rysuj_pet(adres_okna);
	for (auto& slupkixd : slupki)
	{
		slupkixd.draw(adres_okna);
	}

}
void gra::sterowanie()
{
	ptak.sterowanie();
}
void gra::pozycja_kamery()
{
	oknogra.setPosition(kamera->getCenter().x - 400, kamera->getCenter().y - 300);
	kamera->setCenter(ptak.ptak_ksztalt_return()->getPosition().x+230, 300.f);
	
}
void gra::silnikfizyczny()
{
	for (auto& slupki : slupki)
	{
		if (ptak.ptak_ksztalt_return()->getGlobalBounds().intersects(slupki.zwroc_slupek()->getGlobalBounds()))
		{
			ptak.ptak_ksztalt_return()->setFillColor(sf::Color::Red);
		}
	}
}
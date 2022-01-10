#include "Gra.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (ekran==0)
		{
			ekran = 1;
			okno_koniec_gry = new Koniec_gry(kamera->getCenter().x - kamera->getSize().x / 4, kamera->getCenter().y - kamera->getSize().y / 4, kamera);
		}
	}
	*/

gra::gra(sf::RenderWindow *adres_okna, sf::View* adres_kamery, sf::Event* adres_zdarzen)
{
	srand(time(NULL));
	kamera = adres_kamery;
	zdarzenie = adres_zdarzen;
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

	if (ekran == 1)
	{
		okno_koniec_gry->draw(adres_okna);
	}

}
void gra::sterowanie()
{
	switch (ekran)
	{
	case 0:
		ptak.sterowanie();
		break;
	}
}

void gra::sterowanie_event()
{
	switch (ekran)
	{
	case 1:
		okno_koniec_gry->sterowanie(adres_okna, zdarzenie, menu_selected_flag);
		break;
	}
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
			ptak.ustaw_czy_zyje(false);
			koniec_gry = true;
		}
	}

}

void gra::aktualizuj()
{
	sterowanie();
	pozycja_kamery();
	silnikfizyczny();
	if(ekran ==0) sprawdz_czy_koniec();
	draw();
}

void gra::sprawdz_czy_koniec()
{
	if (koniec_gry == true)
	{
		std::cout << "jest git";
		ekran = 1;
		okno_koniec_gry = new Koniec_gry(kamera->getCenter().x -300.f, kamera->getCenter().y - 200.f, kamera);
	}
}
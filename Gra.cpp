#include "Gra.h"
#include <SFML/Graphics.hpp>
#include <iostream>

gra::gra(sf::RenderWindow *adres_okna, sf::View* adres_kamery, sf::Event* adres_zdarzen, int* aktualny_ekran, unsigned int* poziom_gry)
{//ladowanie czcionki
	if (!czcionka.loadFromFile("arial.ttf"))
	{
		std::cout << "Problem z czcionka" << std::endl;
	}
//cechy wygladowe licznika wyniku
	wynik_tekst.setFont(czcionka);
	wynik_tekst.setPosition(-88.f, 16.f);
	wynik_tekst.setFillColor(sf::Color::Magenta);
	wynik_tekst.setCharacterSize(30);
	wynik_tekst.setString("Wynik: 0");
//ustawianie okna gry
	this->aktualny_ekran = aktualny_ekran;
	staty_gra.numer_poziomu = *poziom_gry;
	kamera = adres_kamery;
	zdarzenie = adres_zdarzen;
	oknogra.setPosition(0, 0);
	oknogra.setSize({ 800,600 });

	slupki.reserve(10);
//ustawienie tla i predkosci ptaka w zaleznosci od poziomu gry

	switch (*poziom_gry)
	{
	case 1:
		teksturaa->loadFromFile("tlo.png");
		ptak.ustaw_predkosc(3.f);
		break;
	case 2:
		teksturaa->loadFromFile("tlo2.png");
		ptak.ustaw_predkosc(5.f);
		break;
	case 3:
		teksturaa->loadFromFile("tlo3.png");
		ptak.ustaw_predkosc(7.f);
		break;
	}
	
	oknogra.setTexture(teksturaa);
	this->adres_okna = adres_okna;
	ptak.ptak_ksztalt_return()->setPosition({ 70, 256 });
	for (int i=0;i<5;i++)
	{
		int x;
		x = -100 + rand() % 200;
		slupki.emplace_back(337.f+i*260.f, 0.f, 182.f+x);
		slupki.emplace_back(337.f+i*260.f, 352.f+x, 248.f-x);
	}

}

gra::~gra()
{
	delete teksturaa;
}

void gra::draw()
{

	adres_okna->draw(oknogra);
	ptak.rysuj_pet(adres_okna);
	for (auto& slupkixd : slupki)
	{
		slupkixd.draw(adres_okna);
	}

	adres_okna->draw(wynik_tekst);

	if (ekran == 1 || ekran == 3)
	{
		okno_koniec_gry->draw(adres_okna);
	}

	if (ekran == 2)
	{
		adres_okna->draw(*okno_pomocy);
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
//sterowanie ekranem podczas rozgrywki
void gra::sterowanie_event()
{
	switch (ekran)
	{
	case 0:
		if (zdarzenie->type == sf::Event::KeyReleased)
		{
			if (zdarzenie->key.code == sf::Keyboard::F1)
			{
				ekran = 2;
				okno_pomocy = new sf::RectangleShape;
				tekstura_pomocy = new sf::Texture;

				tekstura_pomocy->loadFromFile("pomoc.png");
				okno_pomocy->setSize({800.f,600.f});
				okno_pomocy->setPosition(kamera->getCenter().x - 400.f, kamera->getCenter().y - 300.f);
				okno_pomocy->setTexture(tekstura_pomocy);
			}
			if (zdarzenie->key.code == sf::Keyboard::Escape)
			{
				ekran = 3;
				okno_koniec_gry = new Koniec_gry(kamera->getCenter().x - 300.f, kamera->getCenter().y - 200.f, kamera, aktualny_ekran, &ekran);
			}
		}
		break;
	case 1:
	case 3:
		okno_koniec_gry->sterowanie(adres_okna, zdarzenie);
		break;
	case 2:
		if (zdarzenie->type == sf::Event::KeyReleased)
		{
			if (zdarzenie->key.code == sf::Keyboard::F1)
			{
				ekran = 0;
				delete okno_pomocy;
				delete tekstura_pomocy;
			}
		}
		break;
	}
}

void gra::pozycja_kamery()
{
	oknogra.setPosition(kamera->getCenter().x - 400.f, kamera->getCenter().y - 300.f);
	kamera->setCenter(ptak.ptak_ksztalt_return()->getPosition().x+230, 300.f);
	switch(staty_gra.numer_poziomu)
	{
	case 1:
		wynik_tekst.move(3.f, 0.f);
		break;
	case 2:
		wynik_tekst.move(5.f, 0.f);
		break;
	case 3:
		wynik_tekst.move(7.f, 0.f);
		break;
	}
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

	if (ptak.ptak_ksztalt_return()->getPosition().x > 337.f + 260.f * staty_gra.wynik)
	{
		staty_gra.wynik++;
		ile_ma_za_soba++;
		wynik_tekst.setString("Wynik: " + std::to_string(staty_gra.wynik));
	}

	if (ile_ma_za_soba == 2)
	{
		int x;

		// Usuwamy 2 pierwsze s?upki
		slupki.erase(slupki.begin());
		slupki.erase(slupki.begin());
		
		// Wstawiamy 2 nowe s?upki na koniec kontenera
		x = -100 + rand() % 200;
		slupki.emplace_back(337.f + (staty_gra.wynik + 3) * 260.f, 0.f, 182.f + x); // +3 bo 3 szczeliny s? przed nim
		slupki.emplace_back(337.f + (staty_gra.wynik + 3) * 260.f, 352.f + x, 248.f - x);
		ile_ma_za_soba--;
	}

}

void gra::aktualizuj()
{
	sterowanie();
	silnikfizyczny();
	if (ekran == 0)
	{
		pozycja_kamery();
		sprawdz_czy_koniec();
	}
	draw();
}

void gra::sprawdz_czy_koniec()
{
	if (koniec_gry == true)
	{
		ekran = 1;
		okno_koniec_gry = new Koniec_gry(kamera->getCenter().x -300.f, kamera->getCenter().y - 200.f, kamera, aktualny_ekran, &ekran);
		zapisz_statystyki_do_pliku();
	}
}

void gra::zapisz_statystyki_do_pliku()
{
	std::fstream plik;
	plik.open("staty.txt", std::ios::app | std::ios::binary);
	if (plik.good() == true)
	{
		plik.write((char*)&staty_gra, sizeof(staty_gra));
	}
	else
	{
		std::cout << "Problem z plikiem" << std::endl;
	}
	plik.close();
}
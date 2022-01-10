#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "pet.h"
#include "slupki.h"
#include "menu.h"


class gra
{
public:
	gra(sf::RenderWindow *adres_okna, sf::View* adres_kamery, sf::Event* adres_zdarzen);
	void draw();
	void sterowanie();
	void pozycja_kamery();
	void silnikfizyczny();
	void aktualizuj();
	void sprawdz_czy_koniec();
	void sterowanie_event();
private:
	pet ptak;
	sf::RenderWindow *adres_okna;
	sf::Event* zdarzenie;
	sf::RectangleShape oknogra;
	sf::Texture* teksturaa = new sf::Texture;
	sf::View* kamera;
	std::vector<slupki> slupki;
	unsigned int ekran = 0; // 0 - brak ekranu , 1 - menu koniec gry, 2 - ekran pomocy
	Koniec_gry* okno_koniec_gry = 0;
	bool koniec_gry = false;
	int menu_selected_flag = 0;
};

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "pet.h"
#include "slupki.h"
#include "menu.h"
#include <fstream>

class gra
{
public:
	gra(sf::RenderWindow *adres_okna, sf::View* adres_kamery, sf::Event* adres_zdarzen, int* aktualny_ekran, unsigned int* poziom_gry);
	~gra();
	void draw();
	void sterowanie();
	void pozycja_kamery();
	void silnikfizyczny();
	void aktualizuj();
	void sprawdz_czy_koniec();
	void sterowanie_event();
	void zapisz_statystyki_do_pliku();

private:
	pet ptak;
	sf::RenderWindow *adres_okna;
	sf::Event* zdarzenie;
	sf::RectangleShape oknogra;
	sf::Texture* teksturaa = new sf::Texture;
	sf::View* kamera;
	std::vector<slupki> slupki;
	unsigned int ekran = 0; // 0 - brak ekranu , 1 - menu koniec gry, 2 - ekran pomocy , 3 - ekran ESC
	Koniec_gry* okno_koniec_gry = 0;
	bool koniec_gry = false;
	int* aktualny_ekran;
	sf::Text wynik_tekst;
	sf::Font czcionka;
	sf::RectangleShape* okno_pomocy = 0;
	sf::Texture* tekstura_pomocy = 0;
	Staty staty_gra;
	int ktory_slupek = 0;
	int ile_ma_za_soba = 0;

};

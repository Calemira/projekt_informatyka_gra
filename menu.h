#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "animacja.h"

struct Staty
{
	unsigned int wynik = 0;
	unsigned int numer_poziomu;
};

class Menu
{
private:
	sf::RectangleShape* pet_menu = 0;
	sf::Texture* pet_tekstura = 0;
	animacja* pet_animacja = 0;
	int ktora_klatka = 0;
	double klatka_timer = 0.0;

protected:
	sf::Font font;
	sf::Text* menu = 0;
	int selectedItem = 0;
	sf::View* kamera = 0;
	sf::RectangleShape naglowek;
	sf::Text tytul;
	sf::RectangleShape pole_glowne;
	int* aktualny_ekran = 0;
	unsigned int liczba_przyciskow = 0;

public:
	Menu( sf::View* adres_kamery, int* aktualny_ekran);
	Menu() = default;
	virtual ~Menu();
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; }
	virtual void draw(sf::RenderWindow* window);
	virtual void sterowanie(sf::RenderWindow* window, sf::Event* event);
	void animuj();
	void inicjalizacja_animacji();
};

class Koniec_gry : public Menu
{
public:
	Koniec_gry(float x, float y, sf::View* adres_kamery, int* aktualny_ekran, unsigned int* ekran);
	~Koniec_gry() = default;
	void sterowanie(sf::RenderWindow* window, sf::Event* event);
private:
	unsigned int* ekran;
};

class Menu_Poziom_Wybor : public Menu
{
public:
	Menu_Poziom_Wybor(sf::View* adres_kamery, int* aktualny_ekran, unsigned int* poziom_gry);
	~Menu_Poziom_Wybor() = default;
	void sterowanie(sf::RenderWindow* window, sf::Event* event);
private:
	unsigned int* poziom_gry;
};

class Historia_Wynikow : public Menu
{
public:
	Historia_Wynikow(sf::View* adres_kamery, int* aktualny_ekran);
	~Historia_Wynikow() = default;
	void sterowanie(sf::RenderWindow* window, sf::Event* event);
	void resetuj_statystyki();
	void draw(sf::RenderWindow* window);
	void odczyt_statystyk_z_pliku();
private:
	sf::Text wyniki[10];
	Staty staty_menu[10];
};



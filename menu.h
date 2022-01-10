#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>




class Menu
{
protected:
	sf::Font font;
	sf::Text* menu;
	int selectedItem = 0;
	sf::View* kamera = 0;
	sf::RectangleShape naglowek;
	sf::Text tytul;
	sf::RectangleShape pole_glowne;
	int* aktualny_ekran;
	unsigned int liczba_przyciskow;

public:
	Menu( sf::View* adres_kamery, int* aktualny_ekran);
	Menu() = default;
	virtual ~Menu() = default;
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow* window);
	virtual void sterowanie(sf::RenderWindow* window, sf::Event* event);
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




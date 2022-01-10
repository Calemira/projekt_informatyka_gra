#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_LICZBA_POZIOMOW 3


class Menu
{
protected:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];
	int selectedItem = 0;
	sf::View* kamera = 0;
	sf::RectangleShape naglowek;
	sf::Text tytul;
	sf::RectangleShape pole_glowne;

public:
	Menu( sf::View* adres_kamery);
	Menu() = default;
	~Menu() {};
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow* window);
	virtual void sterowanie(sf::RenderWindow* window, sf::Event* event, int& menu_selected_flag);
};

class Koniec_gry : public Menu
{
public:
	Koniec_gry(float x, float y, sf::View* adres_kamery);
	~Koniec_gry() = default;
	void sterowanie(sf::RenderWindow* window, sf::Event* event, int& menu_selected_flag);
private:
	//sf::RectangleShape guziki;
};



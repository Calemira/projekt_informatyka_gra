#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_LICZBA_POZIOMOW 3


class Menu
{

private:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];
	int selectedItem = 0;
	sf::View* kamera;

public:
	Menu(float width, float height, sf::View* adres_kamery);
	~Menu() {};
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow& window);
};



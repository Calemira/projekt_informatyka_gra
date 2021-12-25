#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class slupki
{
private:
	sf::RectangleShape slupek;
public:
	slupki(float x, float y, float height);
	void draw(sf::RenderWindow* oknoslupki);
	sf::RectangleShape* zwroc_slupek() { return &slupek; };
};


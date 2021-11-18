#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Pomoc
{
public:
	Pomoc();
	void draw(sf::RenderWindow& window);
private:
	sf::RectangleShape oknopomoc;
	sf::Texture* tekstura = new sf::Texture;
};


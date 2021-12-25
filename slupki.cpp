#include "slupki.h"

slupki::slupki(float x, float y, float height)
{
	slupek.setPosition(x, y);
	slupek.setSize({ 70, height });
	slupek.setFillColor(sf::Color::Green);
}
void slupki::draw(sf::RenderWindow* oknoslupki)
{
	oknoslupki->draw(slupek);
}


#include "animacja.h"
#include <SFML/Graphics.hpp>
animacja::animacja(sf::Texture* tekstura, int liczba_animacji)
{
	this->liczba_animacji = liczba_animacji;
	animacja_teraz = 0;
	klatka.width = tekstura->getSize().x;
	klatka.height = tekstura->getSize().y / float(liczba_animacji);
}

void animacja::aktualizacja(int linijka)
{
	animacja_teraz = linijka;
	klatka.top = animacja_teraz * klatka.height;
}

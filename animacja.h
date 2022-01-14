#pragma once
#include <SFML/Graphics.hpp>
class animacja
{
public:
	animacja(sf::Texture* tekstura, int liczba_animacji);
	animacja() = default;
	~animacja() = default;
	void aktualizacja(int linijka);
	sf::IntRect klatka_zwroc() { return klatka; }

private:
	sf::IntRect klatka;
	int liczba_animacji;
	int animacja_teraz;
};


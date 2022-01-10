#include "menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

Menu::Menu(sf::View* adres_kamery, int* aktualny_ekran)
{
	liczba_przyciskow = 3;
	menu = new sf::Text[liczba_przyciskow];

	this->aktualny_ekran = aktualny_ekran;

	float width = 800.f;
	float height = 600.f;

	pole_glowne.setPosition({ 0.f,0.f });
	pole_glowne.setSize({ width,height });
	pole_glowne.setFillColor(sf::Color( 49, 165, 80 ));

	naglowek.setPosition({ 0.f,0.f });
	naglowek.setSize({ 800.f,100.f });
	naglowek.setFillColor(sf::Color(105, 196, 215));

	tytul.setFont(font);
	tytul.setString("Flappy Pet");
	tytul.setCharacterSize(40);
	tytul.setPosition({ (naglowek.getSize().x / 2) - 100.f , 25.f });

	//adres_kamery->
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}

	for (int i = 0; i < liczba_przyciskow; i++)
	{
		menu[i].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[i].setPosition(sf::Vector2f(width / 3, height / (liczba_przyciskow + 1) * (i + 1)));
	}

	menu[0].setFillColor(sf::Color(105, 196, 215));
	menu[0].setString("Nowa gra");
	menu[1].setString("Pomoc");
	menu[2].setString(L"Wyjœcie");
	
}

void Menu::draw(sf::RenderWindow* window)
{
	window->draw(pole_glowne);
	window->draw(naglowek);
	window->draw(tytul);
	for (int i = 0; i < liczba_przyciskow; i++)
	{
		window->draw(menu[i]);
	}
}


void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < liczba_przyciskow)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = liczba_przyciskow - 1;
		menu[selectedItem].setFillColor(sf::Color(105, 196, 215));
		menu[selectedItem].setStyle(sf::Text::Bold);
	}


}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < liczba_przyciskow)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= liczba_przyciskow)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color(105, 196, 215));
		menu[selectedItem].setStyle(sf::Text::Bold);
	}

}

void Menu::sterowanie(sf::RenderWindow* window, sf::Event* event)
{
	if (event->type == sf::Event::KeyReleased)
	{
		if (event->key.code == sf::Keyboard::Up)
		{
			przesunG();
		}

		if (event->key.code == sf::Keyboard::Down)
		{
			przesunD();
		}

		
		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 0)
		{
			*aktualny_ekran = 2;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 1)
		{
			// Wstawiæ przekierowanie pomocy;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 2)
		{
			exit(0);
		}
		
	}
}

Koniec_gry::Koniec_gry(float x, float y, sf::View* adres_kamery, int* aktualny_ekran, unsigned int* ekran)
{
	liczba_przyciskow = 3;
	menu = new sf::Text[liczba_przyciskow];

	this->aktualny_ekran = aktualny_ekran;
	this->ekran = ekran;

	float width = 600.f;
	float height = 300.f;

	pole_glowne.setPosition({ x,y });
	pole_glowne.setSize({ width,height });
	pole_glowne.setFillColor(sf::Color(49, 165, 80));

	naglowek.setPosition(pole_glowne.getPosition());
	naglowek.setSize({ width,100.f });
	naglowek.setFillColor(sf::Color(105, 196, 215));

	tytul.setFont(font);
	if (*ekran == 1) { tytul.setString("Koniec Gry"); }
	else if(*ekran == 3) { tytul.setString(L"Co teraz chcesz zrobiæ?"); }
	tytul.setCharacterSize(40);
	tytul.setPosition({ (naglowek.getPosition().x + naglowek.getSize().x / 2) - 100.f , naglowek.getPosition().y + 25.f });

	//adres_kamery->
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}

	for (int i = 0; i < liczba_przyciskow; i++)
	{
		menu[i].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[i].setPosition(sf::Vector2f(pole_glowne.getPosition().x + width / 3, pole_glowne.getPosition().y + naglowek.getSize().y + height / (liczba_przyciskow + 1) * i));
	}
	
	menu[0].setFillColor(sf::Color(105, 196, 215));
	menu[0].setString("Resetuj gre");
	menu[1].setString(L"Wróæ do menu");
	menu[2].setString("Wyjscie z gry");
	


}

void Koniec_gry::sterowanie(sf::RenderWindow* window, sf::Event* event)
{
	if (event->type == sf::Event::KeyReleased)
	{
		if (event->key.code == sf::Keyboard::Escape && *ekran == 3)
		{
			*ekran = 0;
		}

		if (event->key.code == sf::Keyboard::Up)
		{
			przesunG();
		}

		if (event->key.code == sf::Keyboard::Down)
		{
			przesunD();
		}

		
		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 0)
		{
			*aktualny_ekran = 112;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 1)
		{
			*aktualny_ekran = 0;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 2)
		{
			exit(0);
		}
		
	}
}

Menu_Poziom_Wybor::Menu_Poziom_Wybor(sf::View* adres_kamery, int* aktualny_ekran, unsigned int* poziom_gry)
{
	liczba_przyciskow = 4;
	menu = new sf::Text[liczba_przyciskow];

	this->aktualny_ekran = aktualny_ekran;
	this->poziom_gry = poziom_gry;

	float width = 800.f;
	float height = 600.f;

	pole_glowne.setPosition({ 0.f,0.f });
	pole_glowne.setSize({ width,height });
	pole_glowne.setFillColor(sf::Color(49, 165, 80));

	naglowek.setPosition({ 0.f,0.f });
	naglowek.setSize({ 800.f,100.f });
	naglowek.setFillColor(sf::Color(105, 196, 215));

	tytul.setFont(font);
	tytul.setString(L"Wybór Poziomu");
	tytul.setCharacterSize(40);
	tytul.setPosition({ (naglowek.getSize().x / 2) - 100.f , 25.f });

	//adres_kamery->
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}
	for (int i = 0; i < liczba_przyciskow; i++)
	{
		menu[i].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[i].setPosition(sf::Vector2f(width / 3, height / (liczba_przyciskow + 1) * (i + 1)));
	}

	menu[0].setFillColor(sf::Color(105, 196, 215));
	menu[0].setString("Heaven");
	menu[1].setString("Midnight");
	menu[2].setString("Gates of hell");
	menu[3].setString("Menu");

}

void Menu_Poziom_Wybor::sterowanie(sf::RenderWindow* window, sf::Event* event)
{
	if (event->type == sf::Event::KeyReleased)
	{
		if (event->key.code == sf::Keyboard::Up)
		{
			przesunG();
		}

		if (event->key.code == sf::Keyboard::Down)
		{
			przesunD();
		}


		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 0)
		{
			*aktualny_ekran = 1;
			*poziom_gry = 1;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 1)
		{
			*aktualny_ekran = 1;
			*poziom_gry = 2;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 2)
		{
			*aktualny_ekran = 1;
			*poziom_gry = 3;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 3)
		{
			*aktualny_ekran = 0;
		}

	}
}


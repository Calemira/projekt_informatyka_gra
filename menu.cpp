#include "menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

Menu::Menu(sf::View* adres_kamery)
{
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
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color(105, 196, 215));
	menu[0].setString("Nowa gra");
	menu[0].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Pomoc");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Wyjscie");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
	
}

void Menu::draw(sf::RenderWindow* window)
{
	window->draw(pole_glowne);
	window->draw(naglowek);
	window->draw(tytul);
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window->draw(menu[i]);
	}
}


void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color(105, 196, 215));
		menu[selectedItem].setStyle(sf::Text::Bold);
	}


}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color(105, 196, 215));
		menu[selectedItem].setStyle(sf::Text::Bold);
	}

}

void Menu::sterowanie(sf::RenderWindow* window, sf::Event* event, int& menu_selected_flag)
{
	if (event->type == sf::Event::Closed)
		window->close();
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
		if (event->key.code == sf::Keyboard::Escape)
		{
			menu_selected_flag = 0;
		}

		if (menu_selected_flag == 0)
		{
			if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 0)
			{
				menu_selected_flag = 1;
			}

			if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 1)
			{
				menu_selected_flag = 2;
			}

			if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 2)
			{
				exit(0);
			}
		}

		/*if (menu_selected_flag == 0)
		{
			if (event.key.code == sf::Keyboard::Enter && getSelectedItem() == 0)
			{
				menu_selected_flag = 1;
			}

			if (event.key.code == sf::Keyboard::Enter && getSelectedItem() == 1)
			{
				menu_selected_flag = 2;
			}

			if (event.key.code == sf::Keyboard::Enter && getSelectedItem() == 2)
			{
				exit(0);
			}
		}
		*/
	}
}

Koniec_gry::Koniec_gry(float x, float y, sf::View* adres_kamery)
{
	float width = 600.f;
	float height = 300.f;

	pole_glowne.setPosition({ x,y });
	pole_glowne.setSize({ width,height });
	pole_glowne.setFillColor(sf::Color(49, 165, 80));

	naglowek.setPosition(pole_glowne.getPosition());
	naglowek.setSize({ width,100.f });
	naglowek.setFillColor(sf::Color(105, 196, 215));

	tytul.setFont(font);
	tytul.setString("Flappy Pet");
	tytul.setCharacterSize(40);
	tytul.setPosition({ (naglowek.getPosition().x + naglowek.getSize().x / 2) - 100.f , naglowek.getPosition().y + 25.f });

	//adres_kamery->
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		menu[i].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[i].setPosition(sf::Vector2f(pole_glowne.getPosition().x + width / 3, pole_glowne.getPosition().y + naglowek.getSize().y + height / (MAX_LICZBA_POZIOMOW + 1) * i));
	}
	
	menu[0].setFillColor(sf::Color(105, 196, 215));
	menu[0].setString("Resetuj gre");
	menu[1].setString(L"Wróæ do menu");
	menu[2].setString("Wyjscie z gry");
	


}

void Koniec_gry::sterowanie(sf::RenderWindow* window, sf::Event* event, int& menu_selected_flag)
{
	if (event->type == sf::Event::Closed)
		window->close();

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
		if (event->key.code == sf::Keyboard::Escape)
		{
			menu_selected_flag = 0;
		}
		if (menu_selected_flag == 0)
		{
			if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 0)
			{
				menu_selected_flag = 1;
			}

			if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 1)
			{
				menu_selected_flag = 2;
			}

			if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 2)
			{
				exit(0);
			}
		}
	}
}


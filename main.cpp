#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "menu.h"
#include "pet.h"
#include "Gra.h"
#include "pomoc.h"
#define MAX_LICZBA_POZIOMOW 3



int main()
{
	Pomoc pomoc;
	int menu_selected_flag = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy pet");
	sf::View kamera({ 0.f,0.f,800.f,600.f });
	Menu menu(window.getSize().x, window.getSize().y, &kamera);
	window.setFramerateLimit(60);
	//gra program(&window, &kamera);
	gra* program = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					menu.przesunG();
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					menu.przesunD();
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					menu_selected_flag = 0;
				}
				if (menu_selected_flag == 0)
				{
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						menu_selected_flag = 1;
						program=new gra(&window, &kamera);
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
					{
						menu_selected_flag = 2;
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
					{
						exit(0);
					}
				}
			}
		}
		window.clear();
		if (menu_selected_flag == 0)
		{
			menu.draw(window);
		}
		if ((menu_selected_flag == 1)&&(program!=0))
		{
			program->sterowanie();
			program->pozycja_kamery();
			program->silnikfizyczny();
			program->draw();
		}
		if (menu_selected_flag == 2)
		{
			pomoc.draw(window);
		}
		window.setView(kamera);
		window.display();
	}

	return 0;
}